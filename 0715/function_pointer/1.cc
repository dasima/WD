#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Test
{
    public:
        void setValue(const string &s, int a)
        {
            s_ = s;
            a_ = a;
        }

        void print() const
        {
            cout << s_ << " " << a_ << endl;
        }
    private:
        string s_;
        int a_;
};
int main(int argc, const char *argv[])
{
    /*
     *1,函数指针的类型包含了类名???
     *2，指向类的成员函数需要&符号
     */
    void (Test::*func)(const string &, int) = &Test::setValue;
    void (Test::*func2)()const = &Test::print;

    Test t;
    //采用对象使用使用该函数指针
    (t.*func)("hello", 9);
    t.print();
    (t.*func2)();

    Test *pt = &t;
//    (pt -> *func)("test", 99);//error: expected unqualified-id before ‘*’ token
//    采用对象的指针使用该函数指针
    (pt->*func)("test", 99);
    pt -> print();
    (pt->*func2)();

    return 0;
}
