#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){

    int result;
    int x;
    int z;

    string line;
    ifstream input_file("input_2");
    vector<string> action;
    vector<int> value;


    if (input_file.is_open())
   {
     while (getline(input_file, line, ' '))
     {
     
          action.push_back(line);
     
      
     }
    input_file.close();
   }


    for (int i = 0; i <= action.size(); i++)
    {
        if (action[i] == "forward")
        {
            x += stoi(action[i+1]);
            cout << "X is " << x << "\n";

        }
        else if (action[i] == "up")
        {
            z -= stoi(action[i+1]);
            cout << "Z is " << z << "\n";

        }
        else if (action[i] == "down")
        {
            z += stoi(action[i+1]);
            cout << "Z is " << z << "\n";
        }


    }
    result = x * z;
    cout << result << "\n";

    return 0;
}


