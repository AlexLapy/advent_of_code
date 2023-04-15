#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){

    int measurement_increases;

    string line;
    ifstream input_file("input_1");
    vector<int> depth;

    if (input_file.is_open())
   {
     while (getline(input_file, line))
     {
          depth.push_back(stoi(line));
     }
    input_file.close();
   }

    for (int i = 3; i <= depth.size(); i++){

        if ((depth[i]+depth[i-1]+depth[i-2]) > (depth[i-1]+depth[i-2]+depth[i-3])){
            measurement_increases ++;
        }
    }
    cout << measurement_increases << "\n";

    return 0;
}

/*data = open('input.txt', 'r').read().split('\n')*/