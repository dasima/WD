#include "condition.h"
#include "mutual.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Condition::Condition(Mutex &lock)
    :lock_(lock)
{
    if(pthread_cond_init(&cond_, NULL))
        throw std::runtime_error("init empty failed");
}

Condition::~Condition()
{
    if(pthread_cond_destroy(&cond_))
        throw std::runtime_error("destroy empty failed");
}

void Condition::wait()
{
    if(pthread_cond_wait(&cond_, lock_.getMutexLockPtr()))
        throw runtime_error("wait empty failed");
}

void Condition::signal()
{
    if(pthread_cond_signal(&cond_))
        throw std::runtime_error("signal full failed");
}

void Condition::signalAll()
{
    if(pthread_cond_broadcast(&cond_))
        throw runtime_error("broadcast failed");
}
