#include <iostream>
#include <string>
#include <vector>
using namespace std;
class X
{
    friend class Y;
    friend void print(const X &x);
 private:
    int x_;
    int y_;
};
class Y
{
    public:
        void print(const X &x)
        {
            cout << x.x_ << endl;
            cout << x.y_ << endl;
        }
};
void print(const X &x)
{
    cout << x.x_ << endl;
    cout << x.y_ << endl;
}
int main(int argc, const char *argv[])
{
    
    return 0;
}
