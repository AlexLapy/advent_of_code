#if !defined(PUZZLE05)
#define PUZZLE05


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


class Puzzle05
{
public:
	Puzzle05();
	void PrintSolutionA();
	void PrintSolutionB();

private:
	const std::vector<std::string> Input;

	struct Point
	{
		int X = 0;
		int Y = 0;

		bool operator==(const Point& Other) const
		{
			return X == Other.X && Y == Other.Y;
		}
	};

	struct PointHasher
	{
		size_t operator()(const Point& Input) const
		{
			return std::hash<int>{}(Input.X) ^ (std::hash<int>{}(Input.Y) + 0xbeef);
		}
	};

	int CalculateOverLappingVents(bool bIncludeDiagonal);

};

#endif // Puzzle05