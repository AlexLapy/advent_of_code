#include "Puzzle11.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>


// 1669
void Puzzle11::PrintSolutionA()
{
    OctopusMap OctopusMap{ Input };
	std::cout << OctopusMap.CalculateFlashes() << '\n';
}

// 
void Puzzle11::PrintSolutionB()
{
	OctopusMap OctopusMap{ Input };
	std::cout << OctopusMap.FindSimultaneousFlash() << '\n';

}

Puzzle11::Puzzle11()
	: Input(Utilities::ReadAllLinesInFile("input_11.txt"))
{
}


Puzzle11::OctopusMap::OctopusMap(const std::vector<std::string>& Input)
{
	for (const std::string& Line : Input)
	{
		for (char CurrentValue : Line)
		{
			FlatOctopusMap.push_back(CurrentValue - '0');
		}

		if (RowLength == 0)
		{
			RowLength = static_cast<int>(Line.size());
		}
	}
}



int Puzzle11::OctopusMap::CalculateFlashes() 
{
    int TotalFlashs = 0;
    for (int step = 0; step < 100; ++step)
    {
        for (int i = 0; i < FlatOctopusMap.size(); ++i)
        {
            ++FlatOctopusMap[i];
        }
        TotalFlashs += SolveFlash();
    }
    return TotalFlashs;
}

int Puzzle11::OctopusMap::FindSimultaneousFlash()
{
    int Step = 0;
	while (true)
	{
		++Step;
		for (int i = 0; i < FlatOctopusMap.size(); ++i)
		{
			++FlatOctopusMap[i];
		}

		if (SolveFlash() == FlatOctopusMap.size())
		{
			return Step;
		}
	}

	return Step;
}

int Puzzle11::OctopusMap::GoUp(int i) const
{
	return i != -1 && i - RowLength >= 0 ? i - RowLength : -1;
}

int Puzzle11::OctopusMap::GoDown(int i) const
{
	return i != -1 && i + RowLength < FlatOctopusMap.size() ? i + RowLength : -1;
}

int Puzzle11::OctopusMap::GoLeft(int i) const
{
	return i != -1 && i % RowLength >= 1 ? i - 1 : -1;
}

int Puzzle11::OctopusMap::GoRight(int i) const
{
	return i != -1 && i % RowLength < RowLength - 1 ? i + 1 : -1;
}

int Puzzle11::OctopusMap::SolveFlash() 
{
	std::unordered_set<int> IndicesFlashed;
    for (int i = 0; i < FlatOctopusMap.size(); ++i)
    {   
        if (FlatOctopusMap[i] > 9)
        {
        	SolveFlashRecursion(i, IndicesFlashed);
        }
    }
	return static_cast<int>(IndicesFlashed.size());
}


void Puzzle11::OctopusMap::SolveFlashRecursion(int i, std::unordered_set<int>& IndicesFlashed) 
{
    // Si on est hors map ou si on a deja fait de la recursion sur cette case
	if (i == -1 || IndicesFlashed.find(i) != IndicesFlashed.end())
	{
		return;
	}

    // Si plus petit que 9, on augmente et retourne en arriere
    if (FlatOctopusMap[i] < 9)
    {
        ++FlatOctopusMap[i];
        return;
    }

    // On note que cette position a flasher
	IndicesFlashed.insert(i);
    // On remet a 0 la case
    FlatOctopusMap[i] = 0;

    // On fait la recursion sur les 8 cases
	SolveFlashRecursion(GoUp(GoLeft(i)), IndicesFlashed); // TopLeft
	SolveFlashRecursion(GoUp(i), IndicesFlashed); // Top
	SolveFlashRecursion(GoUp(GoRight(i)), IndicesFlashed); // Topright
	SolveFlashRecursion(GoLeft(i), IndicesFlashed); // Left
	SolveFlashRecursion(GoRight(i), IndicesFlashed); // Right
	SolveFlashRecursion(GoDown(GoLeft(i)), IndicesFlashed); // BottomLeft
	SolveFlashRecursion(GoDown(i), IndicesFlashed); // Bottom
	SolveFlashRecursion(GoDown(GoRight(i)), IndicesFlashed); // BottomRight
}

