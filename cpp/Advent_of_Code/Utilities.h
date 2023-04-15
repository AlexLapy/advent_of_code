#pragma once

#include <string>
#include <vector>

class Utilities
{
public:
	static std::vector<std::string> ReadAllLinesInFile(std::string Path);
	static std::vector<std::string> SplitString(const std::string& String, const std::string& Delimiter);
	static std::vector<int> ReadCommaSeparatedIntegers(const std::string& String);

	static void VerifyElseCrash(bool bAssert);
	static void VerifyNotReached();
};

