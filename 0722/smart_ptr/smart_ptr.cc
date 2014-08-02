#include "smart_ptr.h"

using namespace std;

SmartPtr::SmartPtr()
    :ptr_(NULL)
{
}

SmartPtr::SmartPtr(Animal *ptr)
    :ptr_(ptr)
{
}

SmartPtr::~SmartPtr()
{
    delete ptr_;
}

void SmartPtr::resetPtr(Animal *ptr)
{
    if(ptr != ptr_)
    {
        delete ptr_;
        ptr_ = ptr;
    }
}

const Animal *SmartPtr::getPtr() const
{
    return ptr_;
}

Animal &SmartPtr::operator*()
{
    return *ptr_;
}

const Animal &SmartPtr::operator*() const
{
    return *ptr_;
}

Animal *SmartPtr::operator->()
{
    return ptr_;
}

const Animal *SmartPtr::operator->() const
{
    return ptr_;
}

