#include "string.h"

String::String()
{
    str_ = new char;
    str_[0] = 0;
}

String::String(const char* s)
{
    str_ = new char[strlen(s) + 1];
    strcpy(str_, s);
}

String::String(const String &S)
{
    str_ = new char[S.size() + 1];
    strcpy(str_, S.str_);
}

std::size_t String::size() const
{
    return strlen(str_);
}

void String::debug()
{
    std::cout << str_ << std::endl;
}

String::~String()
{
    delete[] str_;
}

String &String::operator=(const char *str)
{
    //这里的s可能是自身内部的str_
    //所以，需要进行自身判断问题
    if(str_ != str)
    {
        delete[] str_;
        str_ = NULL;
        str_ = new char[::strlen(str) + 1];
        ::strcpy(str_, str);
    }
    return *this;
}

String &String::operator=(const String &S)
{
    //先判断自身判断问题
    if(this != &S)
    {
        delete[] str_;
        str_ = NULL;
        str_ = new char[S.size() + 1];
        ::strcpy(str_, S.str_);
    }
    return *this;
}

String &String::operator+=(const String &s)
{
    char *tmp = new char[size() + s.size() + 1];
    ::strcpy(tmp, str_);
    :: strcat(tmp, s.str_);
    delete[] str_;
    str_ = NULL;
    str_ = tmp;
    return *this;
}

String &String::operator+=(const char *s)
{
    *this += String(s);
    return *this;
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
