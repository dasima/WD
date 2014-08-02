#include "mutual.h"
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <stdexcept>
using namespace std;
Mutex::Mutex()
{
    if(pthread_mutex_init(&lock_, NULL))
    {
        throw std::runtime_error("mutex init failed!");
    }
}

Mutex::~Mutex()
{
    if(pthread_mutex_destroy(&lock_))
    {
        throw std::runtime_error("destroy lock failed");
    }
}

void Mutex::lock()
{
    if(pthread_mutex_lock(&lock_))
    {
        throw std::runtime_error("lock failed");
    }
}

void Mutex::unlock()
{
    if(pthread_mutex_unlock(&lock_))
    {
        throw std::runtime_error("unlock failed");
    }
}
