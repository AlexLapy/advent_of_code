#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
    ifstream file("input_2");

	if(file.is_open()) {
		string line;
		int depth = 0;
		int horizontal = 0;
		string command;
		int amount;
		while(file >> command >> amount) 
        {
			if(command == "forward") 
            {
				horizontal += amount;
			}
             else if(command == "up") 
            {
				depth -= amount;
			} 
            else if(command == "down")
            {
				depth += amount;
			}
		}
		int solution = depth * horizontal;
		cout << solution << endl;
	}
	file.close();

    ifstream file2("input_2");

    if(file2.is_open()) {
		string line;
		int depth = 0;
        int aim = 0;
		int horizontal = 0;
		string command;
		int amount;
		while(file2 >> command >> amount) 
        {
			if(command == "forward") 
            {
				horizontal += amount;
                depth += (aim * amount);
			}
             else if(command == "up") 
            {
				aim -= amount;
			} 
            else if(command == "down")
            {
				aim += amount;
			}
		}
		int solution = depth * horizontal;
		cout << solution << endl;
	}
	file2.close();


    return 0;
}    