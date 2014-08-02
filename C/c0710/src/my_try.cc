#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    try
    {
        int num ;
        cin >> num;
        if(num == 1)
            throw out_of_range("err1");
        if(num == 2)
            throw invalid_argument("err2");
        cout << num << endl;
    }catch(...)
    {
       cout << "catch a exception" << endl;
    }
    cout << "hello" << endl;
    return 0;
}
