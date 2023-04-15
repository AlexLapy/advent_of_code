#include "Puzzle_12.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>




// 4749
void Puzzle12::PrintSolutionA()
{
	std::cout << FindDistinctPath(false) << '\n';
}

// 
void Puzzle12::PrintSolutionB()
{
	std::cout << FindDistinctPath(true) << '\n';

}

Puzzle12::Puzzle12()
	: Input(Utilities::ReadAllLinesInFile("input_12_test.txt"))
{
}

int Puzzle12::FindDistinctPath(bool bRevisitOneSmallCave)
{
	// Build graph with key=string value=set
	std::unordered_map<std::string, std::unordered_set<std::string>> Graph;

	for (const auto& Line : Input)
	{
		auto Caves = Utilities::SplitString(Line, "-");

        // Could do try_emplace but still works
        // Insert value with key (auto emplace the first time)
		Graph[Caves[0]].insert(Caves[1]);
		Graph[Caves[1]].insert(Caves[0]);
	}

	// Setup initial search state
    // [ [path1] [path2] [path3] ]
	std::vector<std::vector<std::string>> FinishedPaths;
	std::vector<std::vector<std::string>> PreviousPaths;
    // Commence la recherche avec start
	PreviousPaths.push_back(std::vector<std::string> { "start" });


	bool bSearchComplete = false;
	while (!bSearchComplete)
	{
		bSearchComplete = true;
		std::vector<std::vector<std::string>> CurrentPaths;

        // PreviousPath --> [ ["start"] ]
        // PreviousPaths --> [ [] [] [] [] ]
		for (const auto& PreviousPath : PreviousPaths)
		{
            // "start"
			const auto& CurrentLocation = PreviousPath[PreviousPath.size() - 1];

			const auto& ConnectedCaves = Graph.at(CurrentLocation);
			for (const auto& Cave : ConnectedCaves)
			{
				if (Cave == "start")
				{
					continue;
				}

				if (Cave == "end")
				{
					auto FinishedPath = PreviousPath;
					FinishedPath.push_back(Cave);
					FinishedPaths.push_back(FinishedPath);
					continue;
				}

				if (Cave[0] >= 'a' && Cave[0] <= 'z')
				{
					auto bAlreadyVisited = std::find(PreviousPath.begin(), PreviousPath.end(), Cave) != PreviousPath.end();
					if (bAlreadyVisited)
					{
						if (!bRevisitOneSmallCave)
						{
							continue;
						}

						auto bAlreadyRevisitedASmallCave = false;
						for (int i = 1; i < PreviousPath.size(); ++i)
						{
							const auto& PreviousCave = PreviousPath[i];
							if (PreviousCave[0] >= 'a' && PreviousCave[0] <= 'z')
							{
								bAlreadyRevisitedASmallCave = std::find(PreviousPath.begin() + i + 1, PreviousPath.end(), PreviousCave) != PreviousPath.end();
								if (bAlreadyRevisitedASmallCave)
								{
									break;
								}
							}
						}

						if (bAlreadyRevisitedASmallCave)
						{
							continue;
						}
					}
				}
				
				auto CurrentPath = PreviousPath;
				CurrentPath.push_back(Cave);
				CurrentPaths.push_back(CurrentPath);
				bSearchComplete = false;
			}
		}

		PreviousPaths.swap(CurrentPaths);
	}

	return static_cast<int>(FinishedPaths.size());
}
