#include <iostream>
#include <stdexcept>
using namespace std;
class Test{
    public:
        Test()
        {
            cout << "construct...." << endl;
        }
        ~Test()
        {
            cout << "deconstruct...." << endl;
        }
        
};

int main(int argc, const char *argv[])
{
    try
    {
        //栈内存会被释放
        Test t;
        throw runtime_error("error");
    }catch(runtime_error &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
