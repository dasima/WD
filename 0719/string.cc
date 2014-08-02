#include "string.h"
#include <string.h>
using namespace std;

String::String()
    :str_(new char[1])
{
    str_[0] = '\0';
}

String::String(const String &s)
    :str_(new char[s.size() + 1])
{
    ::strcpy(str_, s.str_);
}

String::String(const char *s)
    :str_(new char[strlen(s) + 1])
{
    ::strcpy(str_, s);
}

String &String::operator=(const String &s)
{
    if(this != &s)
    {
        delete[] str_;
        str_ = new char[s.size() + 1];
        strcpy(str_, s.str_);
    }
    return *this;
}

String &String::operator=(const char *s)
{
    if(str_ != s)
    {
        delete[] str_;
        str_ = new char[strlen(s) + 1];
        ::strcpy(str_, s);
    }
    return *this;
}

String &String::operator+=(const String &s)
{
     char *pt = new char[size() + s.size() + 1];
     ::strcpy(pt, str_);
     ::strcpy(pt, s.str_);
     delete str_;
     str_ = pt;

     return *this;
}

String &String::operator+=(const char* s)
{
    return operator+=(String(s));//把s强制转换成String类型，再调用上面的函数
}

void String::debug() const
{
    cout << str_ << endl;
}

size_t String::size() const
{
    return ::strlen(str_);
}

//函数功能为把str_转换成char*类型
const char *String::c_str() const
{
    return str_;
}

String::~String()
{
    delete[] str_;
}

bool operator<(const String &s1, const String &s2)
{
    return ::strcmp(s1.str_, s2.str_) < 0;
}

bool operator>(const String &s1, const String &s2)
{
    return s2 < s1;
}

bool operator<=(const String &s1, const String &s2)
{
    return !(s1 > s2);
}

bool operator>=(const String &s1, const String &s2)
{
    return !(s1 < s2);
}

bool operator==(const String &s1, const String &s2)
{
    return ::strcmp(s1.str_, s2.str_) == 0;
}

bool operator!=(const String &s1, const String &s2)
{
    return !(s1 == s2);
}

char &String::operator[](size_t index)
{
    return str_[index];
}

char String::operator[](size_t index) const
{
    return str_[index];
}
