#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(int argc, const char *argv[])
{
    int i = 7;
    int j = 1;
    int res = 0;
    cout << "before try" << endl;
    try
    {
        if(j == 0)
        {
            throw exception();
        }
        else
        {
            res = i / j;
            cout << "res :" << res << endl;
        }
        cout << "try " << endl;
    }catch(exception &e)
    {
        cout << "catch exception" << endl;
        cout << e.what() << endl;
    }
    cout << "after try" << endl;
  
}
