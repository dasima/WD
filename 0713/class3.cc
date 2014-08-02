#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Test
{
    private:
        int a;
        int b;
    public:
        void set(int a, int b)
        {
            //这里指的是形参a,而不是class的成员a
            //cout << a << endl;
            this -> a = a;
            this -> b = b;
        }
        void print()
        {
            cout << a << " " << b << endl;
        }
};
int main(int argc, const char *argv[])
{
    Test t;
    t.set(9, 8);
    t.print();
    return 0;
}
