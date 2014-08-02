#include "smart_ptr.hpp"
#include <assert.h>

using namespace std;

class Test
{
    public:
        Test()
        {
            cout << "test..." << endl;
        }
        void test()
        {
            cout << "ttt...." << endl;
        }
        ~Test()
        {
            cout << "~test..." << endl;
        }
};
int main(int argc, const char *argv[])
{
    SmartPtr<Test> ptr(new Test);
    ptr->test();
    assert(ptr);
    cout << ptr.getPtr() << endl;

    ptr.resetPtr(NULL);
    assert(ptr == false);

    ptr.resetPtr(new Test);
    assert(ptr);
    
    return 0;
}
