#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, const char *argv[])
{
    string* ps = new string;
    cout << ((*ps) = "decon") << endl;

    string* ps2 = new string("mac");
    cout << *ps2 << endl;

    string* ps3 = new string[9];

    string **ps4 = new string*[9];
    for(int i = 0; i != 9; ++i)
    {
        ps4[i] = new string[7];
      //  ps4[i] = new string("hello");//wrong
    }
    cout << "hh" << endl;
    for(int i = 0; i != 9; ++i)
        delete[] ps4[i];
    delete[] ps4;
    delete ps;
    delete ps2;
    delete []ps3;
    return 0;
}
