#include<iostream>
using namespace std;
class Base
{
    
};

class Derived : public Base
{
    
};

int main(int argc, const char *argv[])
{
    cout << sizeof(Base) << endl;//1
    cout << sizeof(Derived) << endl;//1
    return 0;
}
