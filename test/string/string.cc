#include "string.h"
using namespace std;

String::String()
{
    str_ = new char;
    str_[0] = '\0';
}

String::String(const char* s)
{
    str_ = new char[strlen(s) + 1];
    strcpy(str_, s);
}

String::String(const String& s)
{
    str_ = new char[s.size() + 1];
    strcpy(str_, s.str_);
}

std::size_t String::size() const
{
    return strlen(str_);
}

void String::debug()
{
    cout << str_ << endl;
}

String::~String()
{
    delete str_;
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
