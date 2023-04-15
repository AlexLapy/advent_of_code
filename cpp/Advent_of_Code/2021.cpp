#include <chrono>
#include <iostream>
#include "Puzzle_12.h"


int main()
{
	{
		auto Start = std::chrono::high_resolution_clock::now();
		Puzzle12 Solver;
		Solver.PrintSolutionA();
		auto Stop = std::chrono::high_resolution_clock::now();
		auto DurationMs = std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start);
		std::cout << "Solved part one in " << DurationMs.count() << " ms.\n\n";
	}

	{
		auto Start = std::chrono::high_resolution_clock::now();
		Puzzle12 Solver;
		Solver.PrintSolutionB();
		auto Stop = std::chrono::high_resolution_clock::now();
		auto DurationMs = std::chrono::duration_cast<std::chrono::milliseconds>(Stop - Start);
		std::cout << "Solved part two in " << DurationMs.count() << " ms.\n\n";
	}
}


