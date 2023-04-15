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
#include <set>
#include "Utilities.h"



class Puzzle12
{
public:
	Puzzle12();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;


    int FindDistinctPath(bool bRevisitOneSmallCave);

};



