#ifndef _STRING_H_
#define _STRING_H_ 
#include <iostream>
#include <string.h>
class String{
    public:
        String();
        String(const char*);
        String(const String&);
        void debug();
        std::size_t size() const;
        ~String();
        String &operator=(const String &);
    private:
        char *str_;
        
};
#endif  /*_STRING_H_*/
