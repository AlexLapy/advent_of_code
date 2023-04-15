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



class Puzzle10
{
public:
	Puzzle10();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

    

    struct Scores
    {
        int SyntaxErrorScores;
        int64_t AutoCompleteScores;
    };

    Scores FindSyntaxErrorScore();
    


};



