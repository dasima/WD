#include <iostream>

using namespace std;

class Base
{
    public:
        virtual ~Base()
        {
            cout << "base" << endl;
        }
};
class Derived : public Base
{
    public:
        ~Derived()
        {
            cout << "derived" << endl;
        }
};
int main(int argc, const char *argv[])
{
    Base *p = new Derived;
    delete p;
    return 0;
}
