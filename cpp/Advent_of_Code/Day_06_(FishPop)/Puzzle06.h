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
#include "Utilities.h"


class Puzzle06
{
public:
	Puzzle06();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

	int CalculateFishPopulation();
	int64_t CalculateFishPopulationWithArray();


};
