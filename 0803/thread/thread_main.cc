#include "non_copyable.h"
#include "thread.h"
#include <iostream>
using namespace std;

void *threadFunc(void *arg)
{
    cout << "指针函数的调用..." << endl;
}

int main(int argc, const char *argv[])
{
    Thread t(threadFunc);
    t.start();
    t.join();
    //pthread_detach是在析构函数中，程序正常退出情况下，调用析构函数，执行detach函数；可是程序在非正常情况下退出时，需要回收资源，所以这里用了pthread_join函数
    
    return 0;
}
