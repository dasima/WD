#include <iostream>

using namespace std;

class Base
{
    public:
        virtual void print() const
        {
            cout << "in base" << endl;
        }
        void test()
        {
            cout << "test" << endl;
        }
    private:
        int a_;
        int c_;
};

class Derived : public Base
{
    public:
        void print() const
        {
            cout << "in derived" << endl;
        }
    private:
//        int b_;
};

int main(int argc, const char *argv[])
{
    Base *pb = new Derived;
    pb -> print();

    cout << "sizeof base" << sizeof(Base) << endl;
    cout << "sizeof derived: " << sizeof(Derived) << endl;
    delete pb;
    return 0;
}
