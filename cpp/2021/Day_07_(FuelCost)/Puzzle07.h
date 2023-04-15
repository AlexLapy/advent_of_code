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


class Puzzle07
{
public:
	Puzzle07();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

	int CalculateFuelCost();
	int CalculateFuelCostAdvance();


};
