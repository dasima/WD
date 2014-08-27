#include <iostream>
#include "word_unique.h"
#include <echo/exception.h>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    ifstream in;
    string s = "../data/index.txt";
    in.open(s.c_str());
    if(!in)
        throw Exception("open file failed");
    string line;
    int fsize;
    if(getline(in, line))
    {
        istringstream iss(line);
        iss >> fsize;
        iss >> fsize;
        //cout << fsize << "???" << endl;
    }
    WordUnique wu;
    wu.getDoc();
    return 0;
}
