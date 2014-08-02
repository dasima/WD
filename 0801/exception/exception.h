#ifndef EXCEPTION_H_
#define EXCEPTION_H_ 

#include <string>
#include <exception>

class Exception : public std::exception
{
    public:
        Exception(const char*);
        Exception(const std::string &);
        virtual ~Exception() throw();//这个函数不抛出异常
        virtual const char* what() const throw();
    private:
        std::string message_;//异常信息
};

#endif  /*EXCEPTION_H_*/
