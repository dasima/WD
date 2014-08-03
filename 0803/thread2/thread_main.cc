#include "thread.h"
#include <iostream>
using namespace std;

void threadFunc()
{
    cout << "void() ..." << endl;
}

void threadFunc2(int i)
{
    cout << "void(int)---bind(&函数名, int)..." << i << endl;
}

int main(int argc, const char *argv[])
{
    Thread t(threadFunc);
    t.start();
    t.join();
    
    Thread t2(bind(&threadFunc2, 9));
    t2.start();
    t2.join();

    return 0;
}
