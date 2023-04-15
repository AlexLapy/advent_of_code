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

// std::cout.setf(std::ios::boolalpha);

//using namespace std;


struct BingoBoard
{
    void SolveBoard(const std::vector<int>& CalledNumbers);
    std::vector<int> Numbers;
    std::vector<bool> MarkedSpaces;
    int FinalScore;
    int WinningTurn;
};


int main()
{
    std::vector<int> DrawNumbers;

    std::ifstream file("Day_04/input_04.txt");
    std::string line;
    std::vector<std::string> Input;


    // Read file and add each line to vector
    if (file.is_open())
    {
    while (getline(file, line))
        {
            Input.push_back(line);
        }
    }
    file.close();

    
    // Read called numbers
    std::stringstream DrawNumbersStream{Input[0]};
    std::string CurrentDrawNumber;

    while (getline(DrawNumbersStream, CurrentDrawNumber, ','))
    {
        DrawNumbers.push_back(atoi(CurrentDrawNumber.c_str()));
    }


    // Read bingo board
    std::vector<BingoBoard> BingoBoards;
    int NextBingoBoardLine = 2;
    while (NextBingoBoardLine + 5 <= Input.size())
    {
        BingoBoard CurrentBoard;
        for (int i = NextBingoBoardLine; i < NextBingoBoardLine + 5; ++i)
        {
            std::stringstream BingoBoardLineStream{Input[i]};
            for (int j = 0; j < 5; ++j)
            {
                int CurrentNumber = 0;
                BingoBoardLineStream >> CurrentNumber;

                CurrentBoard.Numbers.push_back(CurrentNumber);
                CurrentBoard.MarkedSpaces.push_back(false);
            }
        }

        BingoBoards.push_back(CurrentBoard);

        NextBingoBoardLine += 6;
    }



   // Solve all the bingo boards
   for (BingoBoard& CurrentBoard : BingoBoards) 
   {
       CurrentBoard.SolveBoard(DrawNumbers);
   }

   auto FirstWinningTurn = DrawNumbers.size();
   auto LastWinningTurn = 0;

   auto WinningScore = 0;
   auto LosingScore = 0;
   for (const auto &CurrentBoard : BingoBoards)
   {
       if (CurrentBoard.WinningTurn < FirstWinningTurn)
       {
           WinningScore = CurrentBoard.FinalScore;
           FirstWinningTurn = CurrentBoard.WinningTurn;
       }
       if (CurrentBoard.WinningTurn > LastWinningTurn)
       {
           LosingScore = CurrentBoard.FinalScore;
           LastWinningTurn = CurrentBoard.WinningTurn;
       }
   }

   
   std::cout << "Winning score is --> " << WinningScore << "\n";
   std::cout << "Losing score is --> " << LosingScore << "\n";



   return 0;
}



void BingoBoard::SolveBoard(const std::vector<int>& CalledNumbers)

{
    for (int i = 0; i < CalledNumbers.size(); ++i)
    {
        // Check if we have current called number
        int CurrentNumber = CalledNumbers[i];
        // std::vector<int>::iterator 
        auto FindResult = std::find(Numbers.begin(), Numbers.end(), CurrentNumber);
        if (FindResult == Numbers.end())
        {
            continue;
        }

        // Mark the called number if found 
        auto CurrentNumberIndex = FindResult - Numbers.begin();
        MarkedSpaces[CurrentNumberIndex] = true;

        // Check if row completed
        auto CurrentRow = CurrentNumberIndex / 5;
        auto RowStartIndex = CurrentRow * 5;
        auto bRowComplete = true;
        for (int j = RowStartIndex; j < RowStartIndex + 5; ++j)
        {
            if (!MarkedSpaces[j])
            {
                bRowComplete = false;
                break;
            }
        }

        // Check if column completed
        auto CurrentColumn = CurrentNumberIndex % 5;
        auto bColComplete = true;

        for (int j = CurrentColumn; j < MarkedSpaces.size(); j += 5)
        {
            if (!MarkedSpaces[j])
            {
                bColComplete = false;
                break;
            }
        }

        // If row or column completed, get score "line * DrawNumber"
        if (bRowComplete || bColComplete)
        {
            WinningTurn = i;
            auto SumOfUnmarkedSpaces = 0;
            for (int j = 0; j < MarkedSpaces.size(); ++j)
            {
                if (!MarkedSpaces[j])
                {
                    SumOfUnmarkedSpaces += Numbers[j];
                }
            }
            FinalScore = SumOfUnmarkedSpaces * CurrentNumber;

            break;
        }

    }
}