#include "thread.h"
#include <iostream>
using namespace std;

class Foo
{
    public:
        void bar()
        {
            cout << "class..void()---bind(&类成员， &类对象).." << endl;
        }

        void bar2(int i)
        {
            cout << "class..void(int)---bind(&类成员， &类对象, int）" << endl;
        }
};

int main(int argc, const char *argv[])
{
    Foo foo;
    Thread t(bind(&Foo::bar, &foo));//类绑定隐含一个对象
    t.start();
    t.join();

    Thread t2(bind(&Foo::bar2, &foo, 9));
    t2.start();
    t2.join();
    return 0;
}
