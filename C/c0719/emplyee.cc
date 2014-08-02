#include "emplyee.h"
int Emplyee::count_ = 1;
Emplyee::Emplyee()
    :name_(""), id_(count_)
{
    ++count_;
}

Emplyee::Emplyee(std::string name)
    :name_(name), id_(count_)
{
    ++count_;
}

Emplyee::Emplyee(const Emplyee &emp)
    :name_(emp.name_), id_(count_)
{
    ++count_;
}

Emplyee &Emplyee::operator=(const Emplyee &emp)
{
    name_ = emp.name_;
    return *this;
}

Emplyee::~Emplyee()
{
}
