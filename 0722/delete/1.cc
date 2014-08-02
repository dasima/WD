#include <iostream>
using namespace std;

class Base
{
    public:
        Base()
        {
            cout << "Base..." << endl;
        }
        ~Base()
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
//~Base...
int main(int argc, const char *argv[])
{
    Base *pb = new Derived;
    delete pb;
    return 0;
}
