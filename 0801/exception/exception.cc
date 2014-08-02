#include "exception.h"

Exception::Exception(const char *s)
    :message_(s)
{

}

Exception::Exception(const std::string &s)
    :message_(s)
{

}

Exception::~Exception() throw()
{
    
}

const char* Exception::what() const throw()
{
    return message_.c_str();
}
