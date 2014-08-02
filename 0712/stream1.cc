#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, const char *argv[])
{
    string line = "hello world ";
    istringstream is(line);

    string word;
    while(is >> word)
    {
        cout << word << endl;
    }
    return 0;
}
