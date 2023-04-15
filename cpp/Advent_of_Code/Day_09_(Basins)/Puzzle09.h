#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <numeric>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "Utilities.h"



class Puzzle09
{
public:
	Puzzle09();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

    int FindAllLowPointsOfHightMap();

    int SumOfAllLowPoints = 0;
    int SumOfLargestBasins = 0;

    std::vector<int> LowHeightMap;
    std::vector<int> BaseHeightMap;

    int RowSize = 0;
    int ColSize = -1;

    std::vector<std::vector<int>> Basins;

    class Heightmap
	{
	public:
		Heightmap(const std::vector<std::string>& Input);
		int CalculateRiskValue() const;
		int CalculateBasinScore() const;

	private:
		std::vector<int> FlatHeightmap;
		std::vector<int> LowPoints;
		int RowLength = 0;

		int GoUp(int i) const;
		int GoDown(int i) const;
		int GoLeft(int i) const;
		int GoRight(int i) const;

		int CalculateBasinSize(int i) const;
		void CalculateBasinSize(int i, std::unordered_set<int>& IndicesInBasin) const;
	};


    void CornerCheck(int location);
    void MiddleCheck(int location);
    void BorderCheck(int location);
};



