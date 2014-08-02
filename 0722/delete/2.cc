#include <iostream>
using namespace std;

class Base
{
    public:
        Base()
        {
            cout << "Base..." << endl;
        }
        virtual ~Base()////虚函数
        {
            cout << "~Base..." << endl;
        }
};

class Derived : public Base
{
    public:
        Derived()
        {
            cout << "derived..." << endl;
        }

        ~Derived()
        {
            cout << "~Derived..." << endl;
        }
};

//Base...
//derived...
//~Derived...
//~Base...
int main(int argc, const char *argv[])
{
    Base *pb = new Derived;
    delete pb;
    return 0;
}
