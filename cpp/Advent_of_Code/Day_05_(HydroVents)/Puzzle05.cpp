#include "Puzzle05.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <unordered_map>

// 5147
void Puzzle05::PrintSolutionA()
{
	std::cout << CalculateOverLappingVents(false) << '\n';
}

// 16925
void Puzzle05::PrintSolutionB()
{
	std::cout << CalculateOverLappingVents(true) << '\n';
}

Puzzle05::Puzzle05()
	: Input(Utilities::ReadAllLinesInFile("input_05.txt"))
{
}

int Puzzle05::CalculateOverLappingVents(bool bIncludeDiagonal)
{
	std::unordered_map<Point, int, PointHasher> HydrothermalVents;
	for (const std::string& CurrentLine : Input)
	{
		// Splitting Input
		std::vector<std::string> CurrentLinePoints = Utilities::SplitString(CurrentLine, " -> ");

		// Creating First Point from first half
		std::vector<std::string> FirstPointAsStrings = Utilities::SplitString(CurrentLinePoints[0], ",");
		Point FirstPoint = { std::atoi(FirstPointAsStrings[0].c_str()), std::atoi(FirstPointAsStrings[1].c_str()) };

		// Creating Second Point from second half
		std::vector<std::string> SecondPointAsStrings = Utilities::SplitString(CurrentLinePoints[1], ",");
		Point SecondPoint = { std::atoi(SecondPointAsStrings[0].c_str()), std::atoi(SecondPointAsStrings[1].c_str()) };

		// Order Point from top to down
		if (FirstPoint.Y > SecondPoint.Y)
		{
			std::swap(FirstPoint, SecondPoint);
		}

		// Order Point from left to right " X has priority "
		if (FirstPoint.X > SecondPoint.X)
		{
			std::swap(FirstPoint, SecondPoint);
		}


		// Add each Points of the horizontal line into the dictionary "map"
		if (FirstPoint.Y == SecondPoint.Y)
		{
			for (int i = FirstPoint.X; i <= SecondPoint.X; ++i)
			{
				Point CurrentPoint = { i, FirstPoint.Y };
				auto Found = HydrothermalVents.find(CurrentPoint);
				if (Found == HydrothermalVents.end())
				{
					HydrothermalVents.emplace(CurrentPoint, 0);	
				}
				++HydrothermalVents[CurrentPoint];
			}
		}

		// Add each Points of the vertical line into the dictionary "map"
		else if (FirstPoint.X == SecondPoint.X)
		{
			for (int i = FirstPoint.Y; i <= SecondPoint.Y; ++i)
			{
				Point CurrentPoint = { FirstPoint.X, i };
				auto Found = HydrothermalVents.find(CurrentPoint);
				if (Found == HydrothermalVents.end())
				{
					HydrothermalVents.emplace(CurrentPoint, 0);	
				}
				++HydrothermalVents[CurrentPoint];
			}
		}

		else if (bIncludeDiagonal)
		{

			// Add each Points of the " \ " line into the dictionary "map"
			if (FirstPoint.Y < SecondPoint.Y)
			{
				int CurrentX = FirstPoint.X;
				int CurrentY = FirstPoint.Y;
				while (CurrentX <= SecondPoint.X && CurrentY <= SecondPoint.Y)
				{
					Point CurrentPoint = { CurrentX, CurrentY };
					auto Found = HydrothermalVents.find(CurrentPoint);
					if (Found == HydrothermalVents.end())
					{
						HydrothermalVents.emplace(CurrentPoint, 0);	
					}
					++HydrothermalVents[CurrentPoint];

					++CurrentX;
					++CurrentY;
				}
			}

			// Add each Points of the " / " line into the dictionary "map"
			else if (FirstPoint.Y > SecondPoint.Y)
			{
				int CurrentX = FirstPoint.X;
				int CurrentY = FirstPoint.Y;
				while (CurrentX <= SecondPoint.X && CurrentY >= SecondPoint.Y)
				{
					Point CurrentPoint = { CurrentX, CurrentY };
					auto Found = HydrothermalVents.find(CurrentPoint);
					if (Found == HydrothermalVents.end())
					{
						HydrothermalVents.emplace(CurrentPoint, 0);	
					}
					++HydrothermalVents[CurrentPoint];

					++CurrentX;
					--CurrentY;
				}
			}
			
		}

	}

	// For each keys, if value >= 2 then increment OverlapCount
	int OverlapCount = 0;
	for (const auto& HydrothermalVent : HydrothermalVents)
	{
		int CurrentValue = HydrothermalVent.second;
		if (CurrentValue >= 2)
		{
			++OverlapCount;
		}
	}	


	return OverlapCount;
}

