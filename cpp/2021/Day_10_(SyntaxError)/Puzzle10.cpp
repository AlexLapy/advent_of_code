#include "Puzzle10.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>



// 464991
void Puzzle10::PrintSolutionA()
{
	std::cout << FindSyntaxErrorScore().SyntaxErrorScores << '\n';
}

// 3662008566
void Puzzle10::PrintSolutionB()
{
	std::cout << FindSyntaxErrorScore().AutoCompleteScores << '\n';

}

Puzzle10::Puzzle10()
	: Input(Utilities::ReadAllLinesInFile("input_10.txt"))
{
}

const std::unordered_map<char, char> OpenerToCloser =
{
	{ '(', ')' },
	{ '[', ']' },
	{ '{', '}' },
	{ '<', '>' }
};

const std::unordered_map<char, char> CloserToOpener =
{
	{ ')', '(' },
	{ ']', '[' },
	{ '}', '{' },
	{ '>', '<' }
};

const std::unordered_map<char, int> CloserToSyntaxErrorScore =
{
	{ ')', 3 },
	{ ']', 57 },
	{ '}', 1197},
	{ '>', 25137 }
};

const std::unordered_map<char, int> CloserToAutocompleteScore =
{
	{ ')', 1 },
	{ ']', 2 },
	{ '}', 3},
	{ '>', 4 }
};

Puzzle10::Scores Puzzle10::FindSyntaxErrorScore()
{
    Scores Result;

    std::vector<int64_t> IncompleteScoreVector;
   
    for (const std::string& Line : Input)
    {
        std::stack<char> Openers;
        bool bLineCorrupt = false;
        for (char CurrentToken : Line)
        {
            if (OpenerToCloser.find(CurrentToken) != OpenerToCloser.end())
            {
                Openers.push(CurrentToken);
            }
            else if (Openers.size() == 0 || OpenerToCloser.at(Openers.top()) != CurrentToken)
            {
                bLineCorrupt = true;
                Result.SyntaxErrorScores += CloserToSyntaxErrorScore.at(CurrentToken);
            }
            else 
            {
                Openers.pop();
            }

            if (bLineCorrupt)
            {
                break;
            }
            
        }

        if (bLineCorrupt)
        {
            continue;
        }

        int64_t CurrentLineScore = 0;
        while (Openers.size() != 0)
        {
            char Token = OpenerToCloser.at(Openers.top());
            char CloserAutocompleteScore = CloserToAutocompleteScore.at(Token);
			CurrentLineScore *= 5;
			CurrentLineScore += CloserAutocompleteScore;
            Openers.pop();  
        }

        IncompleteScoreVector.push_back(CurrentLineScore);
    }

    std::sort(IncompleteScoreVector.begin(), IncompleteScoreVector.end());
    Result.AutoCompleteScores = IncompleteScoreVector[IncompleteScoreVector.size() / 2];

    return Result;
}