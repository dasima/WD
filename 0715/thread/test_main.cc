#include "thread.h"
#include <iostream>
#include <unistd.h>
using namespace std;

/*
 *这个线程类目前只可以接收c函数
 *如果是一个c++成员函数，那么它的指针是
 *void* (Test::*) (void*)
 *后面使用一种工具bind,可实现函数的转化boost::bind
 */
void *threadFunc(void *arg)
{
    while(1)
    {
        sleep(1);
        cout << "function pointer ----->  thread create" << endl;
    }
}
int main(int argc, const char *argv[])
{
    Thread t(threadFunc);
    t.start();
    t.join();
    return 0;
}
