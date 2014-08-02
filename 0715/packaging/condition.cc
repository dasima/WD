#include "condition.h"
#include "mutual.h"
#include <stdexcept>
using namespace std;
Condition::Condition(Mutex &lock)
    :lock_(lock)
{
    if(pthread_cond_init(&cond_, NULL))
    {
        throw std::runtime_error("init empty failed");
    }
}

Condition::~Condition()
{
    if(pthread_cond_destroy(&cond_))
    {
        throw std::runtime_error("destroy empty failed");
    }
}

void Condition::wait()
{
    if(pthread_cond_wait(&cond_, lock_.getMutexLockPtr()))//第二个参数为&lock_,而本函数头文件中声明为Mutex &lock_,所以需要调用Mutex类中函数实现本函数中第二个参数为&lock_的目的，因此Mutex类中定义了返回值为&lock_的成员函数
    {
        throw std::runtime_error("wait empty failed");
    }
}

void Condition::signal()
{
    if(pthread_cond_signal(&cond_))
    {
        throw std::runtime_error("signal full failed");
    }
}

void Condition::signalAll()
{
    if(pthread_cond_broadcast(&cond_))
    {
        throw std::runtime_error("broadcast failed");
    }
}
 
