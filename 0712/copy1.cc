#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[])
{
    string infile = "in.txt";
    string outfile = "out.txt";
    ifstream is;
    ofstream os;
    is.open(infile.c_str());
    os.open(outfile.c_str());

    string line;
    while(getline(is, line))
    {
        os << line << endl;   
    }

    is.close();
    os.close();
    return 0;
}
