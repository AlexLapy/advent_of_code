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



class Puzzle11
{
public:
	Puzzle11();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

    class OctopusMap
	{
	public:
		OctopusMap(const std::vector<std::string>& Input);
		int CalculateFlashes();
		int FindSimultaneousFlash();


	private:
		std::vector<int> FlatOctopusMap;
		int RowLength = 0;


		int GoUp(int i) const;
		int GoDown(int i) const;
		int GoLeft(int i) const;
		int GoRight(int i) const;


		int SolveFlash();
		void SolveFlashRecursion(int i, std::unordered_set<int>& IndicesFlashed);
	};

   
};



