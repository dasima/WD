#include <iostream>
#include <stdexcept>
using namespace std;
int main(int argc, const char *argv[])
{
    try
    {
        int num;
        cin >> num;
        if(num == 1)
            throw out_of_range("test1");
        else if(num == 2)
            throw invalid_argument("test2");
        else
            throw exception();
    }catch(out_of_range &e)
    {
        cout << "out_of_range" << endl;
    }catch(invalid_argument &e)
    {
        cout << "invalid_argument" << endl;
    }catch(...)
    {
        cout << "default" << endl;
    }
    cout << "over" << endl;
    return 0;
}
