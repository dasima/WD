#include "smart_ptr.h"

SmartPtr::SmartPtr()
    :ptr_(NULL)
{
}

SmartPtr::SmartPtr(Student *ptr)
    :ptr_(ptr)
{

}

SmartPtr::~SmartPtr(Student *ptr)
    :ptr_(ptr)
{
}

void SmartPtr::resetPtr(Student *ptr)
{
    if(ptr != ptr_)
    {
        delete ptr_;
        ptr_ = ptr;
    }
}

const Student* SmartPtr::getPtr() const
{
    return ptr_;
}

Student* SmartPtr::operator->()
{
    return ptr_;
}

const Student* SmartPtr::operator->() const
{
    return ptr_;
}

Student &SmartPtr::operator*()
{
    return *ptr_;
}

const Student &SmartPtr::operator*() const
{
    return *ptr_;
}
