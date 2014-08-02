#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

int main(int argc, const char *argv[])
{
    int a;
    if(cin.good())
    {
        cout << "cin is good!" << endl;
    }
    while(cin >> a)
    {
        if(cin.bad())
            throw std::runtime_error("IO stream corrupted");
        if(cin.fail())
        {
            cerr << "bad data!" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits < std::streamsize > :: max(), '\n');
            continue;
        }
        cout << a << endl;
    }
    if(cin.eof())
    {
        cout << "eof!" << endl;
    }
    if(cin.fail())
    {
        cout << "fail" << endl;
    }
    std::string s;
    cin >> s;
    cout << s << endl;
    return 0;
}
