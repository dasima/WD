#include <iostream>
#include <string>
#include <vector>
using namespace std;

class T
{
        int j;
        int i;
    public:
        X(int val)
            :j(val), i(j)
        {
        }
        void print() const
        {
            cout << i << " " << j << endl;
        }
};
int main(int argc, const char *argv[])
{
    T x(9);
    x.print();
    return 0;
}
