#include "handle.h"
#include "animal.h"
#include <iostream>
#include <stddef.h>

using namespace std;

Handle::Handle()
    :ptr_(NULL)
{}

Handle::~Handle()
{
    delete ptr_;
}

Handle::Handle(const Animal &a)
    :ptr_(a.copy())////
{
    
}

Handle::Handle(const Handle &h)
    :ptr_(h.ptr_->copy())/////
{
}

Handle &Handle::operator=(const Handle &h)
{
    if(this != &h)
    {
        delete ptr_;
        ptr_ = h.ptr_->copy();
    }
    return *this;
}

Animal *Handle::operator->()
{
    return ptr_;
}

const Animal *Handle::operator->() const
{
    return ptr_;
}
