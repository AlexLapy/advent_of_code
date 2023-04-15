#include "Puzzle06.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <array>

// 350605
void Puzzle06::PrintSolutionA()
{
	std::cout << CalculateFishPopulation() << '\n';
}

// 1592778185024
void Puzzle06::PrintSolutionB()
{
	std::cout << CalculateFishPopulationWithArray() << '\n';
}

Puzzle06::Puzzle06()
	: Input(Utilities::ReadAllLinesInFile("input_06.txt"))
{
}

int Puzzle06::CalculateFishPopulation()
{
    std::vector<int> FishPopuplation;
    for (const std::string& CurrentLine : Input)
    {
        std::vector<std::string> CurrentLineFish = Utilities::SplitString(CurrentLine, ",");

        for (auto Fish: CurrentLineFish)
        {
        FishPopuplation.push_back(atoi(Fish.c_str()));
        }
    }

    for (int Days = 0; Days < 80; ++Days)
    {
        
        int NewFishCount = 0;
        for (int FishNumber = 0; FishNumber < FishPopuplation.size(); ++FishNumber)
        {

            if (FishPopuplation[FishNumber] == 0)
            {
                FishPopuplation[FishNumber] = 6;
                ++NewFishCount;
            }  
            else
            {
            --FishPopuplation[FishNumber];
            }
            
        }
        while(NewFishCount)
        {
            FishPopuplation.push_back(8);
            --NewFishCount;
        }
    }

    

    return FishPopuplation.size();
}

int64_t Puzzle06::CalculateFishPopulationWithArray()
{
    auto FishPopulation = Utilities::ReadCommaSeparatedIntegers(Input[0]);

    constexpr int DaysInCycle = 9;
    std::array<int64_t, DaysInCycle> FishPopulationByDays{}; 

    for (int Fish : FishPopulation)
    {
        ++FishPopulationByDays[Fish];
    }

    // See bottom file for loop with array "Worth if more than 1 tmp variable"
    for (int Days = 0; Days < 256; ++Days)
    {
        
        int64_t FishOnDayZero = FishPopulationByDays[0];

        for (int FishDays = 0; FishDays < DaysInCycle-1; ++FishDays)
        {
            FishPopulationByDays[FishDays] = FishPopulationByDays[FishDays+1];
            
        }
        
        FishPopulationByDays[6] += FishOnDayZero;
        FishPopulationByDays[8] = FishOnDayZero;

    }


    return std::accumulate(FishPopulationByDays.begin(), FishPopulationByDays.end(), static_cast<int64_t>(0));
}



/*

for ( int i = 0; i < TotalDays; ++i)
{
    std::array<int64_t, DaysInCycle> NextFish{};
    NextFish[6] = CurrentFish[0];
    NextFish[8] = CurrentFish[0];
    for ( int j = 0; j < CurrentFish.size(); ++j)
    {
        NextFish[j - 1] += CurrentFish[j];
    }

    CurrentFish = NextFish;
}

*/


