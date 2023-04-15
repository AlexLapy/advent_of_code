#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int main() 
{
    ifstream file("input_3.txt");

	if(file.is_open()) {
		string line;
        vector<int> gamma_binary;
        vector<int> epsilon_binary;
        int gamma = 0;
        int epsilon = 0;
        int zero = 0;
        int one = 0;
        vector<string> binary_list;
		
		while(file >> line) 
        {
			binary_list.push_back(line);
		}

        for (int i = 0; i < binary_list[0].length(); i++)
        {
            zero = 0;
            one = 0;
            for (int j = 0; j < binary_list.size(); j++)
            {
                if (binary_list[j][i] == '0')
                {
                    zero ++;
                }
                else
                {
                    one++;
                }
            }
            if (zero > one) 
            {
                gamma_binary.push_back(0);
                epsilon_binary.push_back(1);
            }    
            else 
            {
                gamma_binary.push_back(1);
                epsilon_binary.push_back(0);
            }
        }

        for (auto i: gamma_binary)
            cout << i << endl;


        for(int i = 0; i < binary_list[0].length(); i++)
        {
		gamma += (gamma_binary[binary_list[0].length()-1-i] * pow(2,i));
		epsilon += (epsilon_binary[binary_list[0].length()-1-i] * pow(2,i));
        }

        cout << gamma << endl;
        cout << epsilon << endl;

		int solution =  gamma * epsilon;
		cout << solution << endl;
	}
	file.close();


    return 0;
}    