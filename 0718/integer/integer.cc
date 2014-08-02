#include "integer.h"

Integer::Integer(int data)
    :data_(data)
{
}

Integer::~Integer()
{
}

std::ostream &operator<<(std::ostream &os, const Integer &in)
{
    return os << in.data_;
}

Integer &Integer::operator++()
{
    ++data_;
    return *this;
}

Integer Integer::operator++(int)
{
    Integer tmp(*this);
    ++data_;
    return tmp;
}
