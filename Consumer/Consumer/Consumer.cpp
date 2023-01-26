// Consumer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Generator.h>
#include <Windows.h>
#include <iostream>
#include <fstream>


using namespace std;
int main()
{
    GeneratorClass DataGenerator;
    ofstream myfile;
    myfile.open("Result.txt", ios::out);
    if (myfile.fail()) {
        return -1;
    }
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) && DataGenerator.GetEscape() == false) {
            DataGenerator.SetEscape(true);
            continue;
        }
        pair<long long int, short > tmp = DataGenerator.GetValue();
        if (tmp.first == 0 && tmp.second == -1) {
            if (DataGenerator.GetEscape() == true) {
                break;
            }
            else { continue; }
        }
    
        myfile << tmp.first << ',' << tmp.second << endl;
    }
    myfile.close();
}
