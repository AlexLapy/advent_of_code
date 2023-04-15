#include "Utilities.h"
#include <fstream>
#include <assert.h>

std::vector<std::string> Utilities::ReadAllLinesInFile(std::string Path)
{

	std::vector<std::string> AllLines;
	std::ifstream FileStream(Path);
	std::string CurrentLine;
	while (std::getline(FileStream, CurrentLine))
	{
		AllLines.push_back(CurrentLine);
	}

	return AllLines;
}

std::vector<std::string> Utilities::SplitString(const std::string& String, const std::string& Delimiter)
{
	std::vector<std::string> Tokens;
	size_t NextTokenStart = 0;
	while (NextTokenStart < String.size())
	{
		size_t DelimiterStart = String.find(Delimiter, NextTokenStart);
		if (DelimiterStart == std::string::npos)
		{
			DelimiterStart = String.size();
		}

		std::string Token = String.substr(NextTokenStart, DelimiterStart - NextTokenStart);
		Tokens.push_back(Token);

		NextTokenStart = DelimiterStart + Delimiter.size();
	}

	return Tokens;
}

std::vector<int> Utilities::ReadCommaSeparatedIntegers(const std::string& String)
{
	auto IntegersAsStrings = SplitString(String, ",");
	std::vector<int> Integers;
	for (const std::string& IntegerAsString : IntegersAsStrings)
	{
		Integers.push_back(std::atoi(IntegerAsString.c_str()));
	}
	return Integers;
}

void Utilities::VerifyElseCrash(bool bAssert)
{
	assert(bAssert);
	if (!bAssert)
	{
		std::terminate();
	}
}

void Utilities::VerifyNotReached()
{
	VerifyElseCrash(false);
}