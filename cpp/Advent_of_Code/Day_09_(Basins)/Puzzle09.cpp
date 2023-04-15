#include "Puzzle09.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>



// 489
void Puzzle09::PrintSolutionA()
{
	std::cout << FindAllLowPointsOfHightMap() << '\n';
}

// 1056330
void Puzzle09::PrintSolutionB()
{
	Heightmap Heightmap{ Input };
	std::cout << Heightmap.CalculateBasinScore() << '\n';
}

Puzzle09::Puzzle09()
	: Input(Utilities::ReadAllLinesInFile("input_09.txt"))
{
}

int Puzzle09::FindAllLowPointsOfHightMap()
{
    // Set up FlatMap, RowSize and Colsize
    for (const std::string& Line : Input)
    {
        for (char CurrentValue : Line)
        {
            BaseHeightMap.push_back(CurrentValue - '0');
        }

        RowSize = Line.size();
        ++ColSize;
    }

    // Check for Low Point and add to LowMap
    for (int i = 0; i < BaseHeightMap.size(); ++i)
    {

        if (   (i == 0)                              | (i == RowSize - 1)             |
               (i == BaseHeightMap.size() - RowSize) | (i == BaseHeightMap.size() - 1))
        {
            CornerCheck(i);
        }
        else if ( (i / RowSize != 0) & (i / RowSize != ColSize) &
                  (i % RowSize != 0) & ((i + 1) % RowSize != 0) )
        {
            MiddleCheck(i);
        }
        else
        {
            BorderCheck(i);
        }

    }

    // For every LowPoint, add the height + 1
    for (int i = 0; i < LowHeightMap.size(); ++i)
    {
        if (LowHeightMap[i] == 1)
        {
            SumOfAllLowPoints += ( BaseHeightMap[i] + 1 );
        }
    }



    return SumOfAllLowPoints;

}

void Puzzle09::CornerCheck(int location)
{
    if (location == 0)
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location + 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }
    }
    
    else if (location == RowSize - 1)
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location - 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }
    }

    else if (location == BaseHeightMap.size() - RowSize)
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location + 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location - RowSize]))
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }
    }

    else if (location == BaseHeightMap.size() - 1)
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location - 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location - RowSize]))
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }
    } 
}

void Puzzle09::MiddleCheck(int location)
{
    if ( (BaseHeightMap[location] < BaseHeightMap[location - 1]) &
         (BaseHeightMap[location] < BaseHeightMap[location + 1]) &
         (BaseHeightMap[location] < BaseHeightMap[location - RowSize]) & 
         (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) )
    {
        LowHeightMap.push_back(1);
    }
    else 
    {
        LowHeightMap.push_back(0);
    }
}

void Puzzle09::BorderCheck(int location)
{
    if (location / RowSize == 0) // On first Row
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location - 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }   
    }
    else if (location / RowSize == ColSize) //  On last Row
    {
        if ( BaseHeightMap[location] < BaseHeightMap[location - 1] &
            BaseHeightMap[location] < BaseHeightMap[location + 1] &
            BaseHeightMap[location] < BaseHeightMap[location - RowSize] )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }  
    }
    else if (location % RowSize == 0) // On first Column
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location + 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) &
             (BaseHeightMap[location] < BaseHeightMap[location - RowSize]) )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }  
    }
    else if ((location + 1) % RowSize == 0) // On last Column
    {
        if ( (BaseHeightMap[location] < BaseHeightMap[location - 1]) &
             (BaseHeightMap[location] < BaseHeightMap[location + RowSize]) &
             (BaseHeightMap[location] < BaseHeightMap[location - RowSize]) )
        {
            LowHeightMap.push_back(1);
        }
        else
        {
            LowHeightMap.push_back(0);
        }
    }
}


Puzzle09::Heightmap::Heightmap(const std::vector<std::string>& Input)
{
	for (const std::string& Line : Input)
	{
		for (char CurrentValue : Line)
		{
			FlatHeightmap.push_back(CurrentValue - '0');
		}

		if (RowLength == 0)
		{
			RowLength = static_cast<int>(Line.size());
		}
	}

	for (int i = 0; i < FlatHeightmap.size(); ++i)
	{
		int SmallestAdjacentValue = 9;

		int UpIndex = GoUp(i);
		if (UpIndex != -1)
		{
			SmallestAdjacentValue = std::min(SmallestAdjacentValue, FlatHeightmap[UpIndex]);
		}

		int DownIndex = GoDown(i);
		if (DownIndex != -1)
		{
			SmallestAdjacentValue = std::min(SmallestAdjacentValue, FlatHeightmap[DownIndex]);
		}

		int LeftIndex = GoLeft(i);
		if (LeftIndex != -1)
		{
			SmallestAdjacentValue = std::min(SmallestAdjacentValue, FlatHeightmap[LeftIndex]);
		}

		int RightIndex = GoRight(i);
		if (RightIndex != -1)
		{
			SmallestAdjacentValue = std::min(SmallestAdjacentValue, FlatHeightmap[RightIndex]);
		}

		if (FlatHeightmap[i] < SmallestAdjacentValue)
		{
			LowPoints.push_back(i);
		}
	}
}

int Puzzle09::Heightmap::CalculateRiskValue() const
{
	int TotalRiskValue = 0;
	for (int i = 0; i < LowPoints.size(); ++i)
	{
		TotalRiskValue += 1 + FlatHeightmap[LowPoints[i]];
	}
	return TotalRiskValue;
}

int Puzzle09::Heightmap::CalculateBasinScore() const
{
	std::vector<int> BasinSizes;
	for (int i = 0; i < LowPoints.size(); ++i)
	{
		BasinSizes.push_back(CalculateBasinSize(LowPoints[i]));
	}
	std::sort(BasinSizes.begin(), BasinSizes.end(), std::greater<int>{});
	Utilities::VerifyElseCrash(BasinSizes.size() >= 3);
	return BasinSizes[0] * BasinSizes[1] * BasinSizes[2];
}

int Puzzle09::Heightmap::GoUp(int i) const
{
	return i - RowLength >= 0 ? i - RowLength : -1;
}

int Puzzle09::Heightmap::GoDown(int i) const
{
	return i + RowLength < FlatHeightmap.size() ? i + RowLength : -1;
}

int Puzzle09::Heightmap::GoLeft(int i) const
{
	return i % RowLength >= 1 ? i - 1 : -1;
}

int Puzzle09::Heightmap::GoRight(int i) const
{
	return i % RowLength < RowLength - 1 ? i + 1 : -1;
}

int Puzzle09::Heightmap::CalculateBasinSize(int i) const
{
	std::unordered_set<int> IndicesInBasin;
	CalculateBasinSize(i, IndicesInBasin);
	return static_cast<int>(IndicesInBasin.size());
}

void Puzzle09::Heightmap::CalculateBasinSize(int i, std::unordered_set<int>& IndicesInBasin) const
{
	if (i == -1 || FlatHeightmap[i] == 9 || IndicesInBasin.find(i) != IndicesInBasin.end())
	{
		return;
	}

	IndicesInBasin.insert(i);
	CalculateBasinSize(GoUp(i), IndicesInBasin);
	CalculateBasinSize(GoDown(i), IndicesInBasin);
	CalculateBasinSize(GoLeft(i), IndicesInBasin);
	CalculateBasinSize(GoRight(i), IndicesInBasin);
}

