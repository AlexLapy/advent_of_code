#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

vector<int> CountOneByPosition(const vector<string> CurrentInput)
{
    vector<int> CountOfOneByPosition;
    for(int i = 0; i < int(CurrentInput[0].size()); ++i)
        {
            CountOfOneByPosition.push_back(0);
        }

    for(auto CurrentLine : CurrentInput)
    {
        for (int i = 0; i < int(CurrentLine.size()); ++i)
        {
            if (CurrentLine[i] == '1')
            {
                ++CountOfOneByPosition[i];
            }
        }     
    }

    return CountOfOneByPosition;
    
}

int LifeSupport(const vector<string> Input, string type)
{
    char FilterCriteria;
    int CurrentBitPosition = 0;
    vector<string> CurrentInput = Input;
    while (CurrentInput.size() != 1)
    {
        vector<int> CountOfOneByPosition = CountOneByPosition(CurrentInput);
        int CountOfOnes = CountOfOneByPosition[CurrentBitPosition];
        int CountOfZeroz = int(CurrentInput.size()) - CountOfOnes;

        if (type == "oxy") FilterCriteria = CountOfOnes >= CountOfZeroz ? '1' : '0';
        else FilterCriteria = CountOfOnes >= CountOfZeroz ? '0' : '1';

        vector<string> NextInput;
        copy_if(
            CurrentInput.begin(), // start of algo
            CurrentInput.end(),  // end of algo
            back_inserter(NextInput), // where to copy
            [CurrentBitPosition,FilterCriteria] // variable to "pass" to the function
            (const string& CurrentLine) // variable to check logic and to copy if true 
            {
                return CurrentLine[CurrentBitPosition] == FilterCriteria;  // Condition 
            }
        );

        CurrentInput = NextInput;
        ++CurrentBitPosition;
    } 

    return stoi(CurrentInput[0], nullptr, 2);
}



int main() 
{

    ifstream file("input_3.txt");
    string line;
    vector<string> Input;

    // Read file and add each line to vector
	if(file.is_open()) 
    {
		while(file >> line) 
        {
			Input.push_back(line);
		}
	}
	file.close();


    // fill vector of 0 and count '1' line by line from each colum
    vector<int> CountOfOneByPosition = CountOneByPosition(Input);
          
    // Compute gamma
    int GammaRate = 0;
    for (int  CountOfOnes : CountOfOneByPosition)
    {
        int CountOfZeros = Input.size() - CountOfOnes;

        if (CountOfOnes > CountOfZeros)
        {
            ++GammaRate;
        }
        GammaRate <<= 1 ;
    }
    GammaRate >>= 1;

    // Compute gamma

    int mask = 0;
    for(int i = 0;  i < int(CountOfOneByPosition.size()); ++i)
    {
        ++mask;
        mask <<= 1;
    }
    mask >>= 1;

    int EpsilonRate = ~GammaRate & mask;

    cout << EpsilonRate * GammaRate << "\n";



    int co2 = LifeSupport(Input, "co2");
    int oxy = LifeSupport(Input, "oxy");

    cout << co2 << "\n" << oxy << "\n" << co2 * oxy << "\n";
    
    return 0;
}    

