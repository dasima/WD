#include "thread.h"
#include <iostream>
using namespace std;

class Foo
{
    public:
        void bar()
        {
            cout << "bind(&类成员函数， &类对象)..." << endl;
        }

        void bar2(int i)
        {
            cout << "bind(&类成员函数名， &类对象， int)..." << endl;
        }
};

int main(int argc, const char *argv[])
{
    Foo foo;
    Thread t(bind(&Foo::bar, &foo));;
    t.start();
    t.join();

    Thread t2(bind(&Foo::bar2, &foo, 9));
    t2.start();
    t2.join();

    return 0;
}
