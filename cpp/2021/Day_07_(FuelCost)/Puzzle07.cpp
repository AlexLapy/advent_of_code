#include "Puzzle07.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>

// 333755
void Puzzle07::PrintSolutionA()
{
	std::cout << CalculateFuelCost() << '\n';
}

// 94017638
void Puzzle07::PrintSolutionB()
{
	std::cout << CalculateFuelCostAdvance() << '\n';
}

Puzzle07::Puzzle07()
	: Input(Utilities::ReadAllLinesInFile("input_07.txt"))
{
}

int Puzzle07::CalculateFuelCost()
{
    // Fill vector with input
    std::vector<int> CrabsPositionVector = Utilities::ReadCommaSeparatedIntegers(Input[0]);

    // Sort List
    std::sort(CrabsPositionVector.begin(), CrabsPositionVector.end());

    // Find Median
    int MiddlePosition = CrabsPositionVector.size() / 2;
    int Median = CrabsPositionVector[MiddlePosition];

    // Cost for each crab
    int FuelCost = 0;
    for ( int CrabCost : CrabsPositionVector)
    {
        FuelCost += abs(CrabCost - Median);
    }

    return FuelCost;
}




int Puzzle07::CalculateFuelCostAdvance()
{
    // Fill vector with input
    std::vector<int> CrabsPositionVector = Utilities::ReadCommaSeparatedIntegers(Input[0]);

    // Sort List
    std::sort(CrabsPositionVector.begin(), CrabsPositionVector.end());

    // Find Mean
    int Total = std::accumulate(CrabsPositionVector.begin(), CrabsPositionVector.end(), 0);
    int mean = (Total / CrabsPositionVector.size()) ;

    // Cost for each crab
    int FuelCost = 0;
    for ( int CrabCost : CrabsPositionVector)
    {
        int Distance = abs(CrabCost - mean);
        
        while (Distance)
        {
            FuelCost += Distance;
            --Distance;
        }
        
        // FuelCost += Distance * ( Distance + 1 ) / 2;
    }

    return FuelCost;

}