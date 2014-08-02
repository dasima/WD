#ifndef _STRING_H_
#define _STRING_H_ 
#include <iostream>
#include <string.h>
class String
{
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, const String &s);

    friend String operator+(const String &s1, const String &s2);
    friend String operator+(const String &s1, const char *s2);
    friend String operator+(const char* s1, const String &);

    friend bool operator<(const String &s1, const String &s2);
    friend bool operator>(const String &s1, const String &s2);
    friend bool operator<=(const String &s1, const String &s2);
    friend bool operator>=(const String &s1, const String &s2);
    friend bool operator==(const String &s1, const String &s2);
    friend bool operator!=(const String &s1, const String &s2);

    public:
        String();
        String(const char*);
        String(const String &);
        void debug();
        std::size_t size() const;
        ~String();
        String &operator=(const String &s);
        String &operator=(const char *s);

        String &operator+=(const String &s);
        String &operator+=(const char *s);

        char &operator[](size_t index);
        char operator[](size_t index) const;

    private:
        char *str_;
};

inline std::ostream &operator<<(std::ostream &os, const String &s)
{
    return os << s.str_;
}

inline std::istream &operator>>(std::istream &is, String &s)
{
    char buf[1024];
    is >> buf;
    if(is)
    {
        s = buf;
    }
    return is;
}

inline String operator+(const String &s1, const String &s2)
{
    String ret(s1);
    ret += s2;
    return ret;
}

inline String operator+(const String &s1, const char *s2)
{
    return s1 + String(s2); 
}

inline String operator+(const char* s1, const String &s2)
{
    return String(s1) + s2;
}


#endif  /*_STR
          ING_H_*/
