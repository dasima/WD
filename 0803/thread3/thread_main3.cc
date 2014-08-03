#include "thread.h"
#include <iostream>
using namespace std;

class FooThread
{
    public:
        FooThread(int);
        void threadFunc();
        void startThread();
        void joinThread();
    private:
        int cnt_;
        Thread thread_;
};

FooThread::FooThread(int i)
    :cnt_(i), thread_(bind(&FooThread::threadFunc, this))
{
}

void FooThread::threadFunc()
{
    while(1)
    {
        sleep(3);
        cout << "类构造函数中bind(&类成员函数， this指针)...类中直接调用成员函数即可..." << endl;
        cout << "cnt --- " << ++cnt_ << endl;
    }
}

void FooThread::startThread()
{
    thread_.start();
}

void FooThread::joinThread()
{
    thread_.join();
}

int main(int argc, const char *argv[])
{
    FooThread foo(9);
    foo.startThread();
    foo.joinThread();
    return 0;
}

