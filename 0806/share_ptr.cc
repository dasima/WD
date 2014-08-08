#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Test
{
    public:
        Test()
        { cout << "Test" << endl; }
        ~Test()
        { cout << "~Test" << endl; }
};

int main(int argc, const char *argv[])
{
    std::shared_ptr<Test> ptr(new Test);
    cout << "it has " << ptr.use_count() <<" reference " << endl;

    shared_ptr<Test> ptr2(ptr);
    cout << "it has " << ptr.use_count() <<" reference " << endl;

    ptr.reset();
    cout << "after reset ptr, it has " << ptr.use_count() << " reference " << endl;

    ptr2.reset();
    cout << "after reset ptr2 " << endl;
    return 0;
}
