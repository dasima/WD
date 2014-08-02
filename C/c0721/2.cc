#include <iostream>
using namespace std;
class Base{
    public:
        Base()
        {
            cout << "base construct..." << endl;
        }
        virtual ~Base()
        {
            cout << "base deconstruct..." << endl;
        }
    private:
        
};
class Other{
    public:
        Other()
        {
            cout << "other construct..." << endl;
        }
        virtual ~Other()
        {
            cout << "other deconstruct...." << endl;
        }
    private:
        
};
class Derived:Base{
    public:
        Derived()
        {
            cout << "derived construct...." << endl;
        }
        virtual ~Derived()
        {
            cout << "derived deconstruct..." << endl;
        }
    private:
        Other other_;
        
};

int main(int argc, const char *argv[])
{
    Derived der;
    cout << ".................." << endl;
    return 0;
}
