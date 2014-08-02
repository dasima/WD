#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T1, typename T2>
T1 &print(T1 &s, T2 val)
{
    s << val;
    return s;
}

int main(int argc, const char *argv[])
{
    double dval = 0.99;
    float fval = 9.9;
    string str = "this is a string";
    ostringstream oss(str);
    ofstream outFile("result.dat");

    print(cout, -3) << endl;
    print(cout, dval) << endl;
    print(cout, fval) << endl;
    print(cout, str) << endl;

    print(outFile, -3) << endl;
    print(outFile, dval) << endl;
    print(outFile, fval) << endl;
    print(outFile, str) << endl;

    print(oss, -3) << endl;
    print(oss, dval) << endl;
    print(oss, fval) << endl;
    print(oss, str) << endl;
    //????
    cout << oss.str() << endl;
    return 0;
}
