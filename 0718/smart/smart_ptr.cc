#include "smart_ptr.h"

SmartPtr::SmartPtr(Animal *ptr)
    :ptr_(ptr)
{
}

SmartPtr::~SmartPtr()
{
    delete ptr_;
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
