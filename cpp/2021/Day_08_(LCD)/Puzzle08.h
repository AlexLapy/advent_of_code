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
#include <unordered_map>
#include <set>


class Puzzle08
{
public:
	Puzzle08();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

	int FindUniqueNumbers();
	int SumOffAllOutputs();

    void PruneUsingPatternSignalLenght(
    std::unordered_map<char, std::set<char>>& ScrambledSegmentsToPossibleSegments,
    std::vector<std::string> ScrambledPatternSignals
    );

    void PruneUsingTotalSegmentReference(
    std::unordered_map<char, std::set<char>>& ScrambledSegmentsToPossibleSegments,
    std::vector<std::string> ScrambledPatternSignals
    );

    void PruneUsingKnownSegment(
    std::unordered_map<char, std::set<char>>& ScrambledSegmentsToPossibleSegments);

    std::set<char> Intersection(const std::set<char>& Left, const std::set<char>& Right);


};


/*
for (const std::string &ScrambledPatternSignal : ScrambledPatternSignals)
    {
        for (char ScrambledSegment : ScrambledPatternSignal)
        {
        // if not found
        if (SegmentToCount.find(ScrambledSegment) == SegmentToCount.end())
        {
            SegmentToCount.emplace(ScrambledSegment, 0);
        }
        ++SegmentToCount[ScrambledSegment];
        }
    }
    */
