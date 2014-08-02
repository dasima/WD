#ifndef _STRING_H_
#define _STRING_H_ 
#include <iostream>
class String
{
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend std::istream &operator>>(std::istream &, String &);

    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char*, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    public:
        String();
        String(const char *);
        String(const String &);

        String &operator=(const char*);
        String &operator=(const String&);

        String &operator+=(const char*);
        String &operator+=(const String&);

        void debug() const;
        size_t size() const;
        const char *c_str() const;

        char &operator[](size_t index);
        char operator[](size_t index) const;
        ~String();
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

inline String operator+(const String &s1, const char* s2)
{
    return s1 + String(s2);
}

inline String operator+(const char* s1, const String &s2)
{
    return String(s1) += s2;
}


#endif  /*_STRING_H_*/
