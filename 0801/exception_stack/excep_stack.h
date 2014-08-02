#ifndef EXCEPTION_H_
#define EXCEPTION_H_ 

#include <string>
#include <exception>

//编译时使用-rdynamic选项，确保stackTrace带有错误信息

class Exception : public std::exception
{
    public:
        Exception(const char*);
        Exception(const std::string &);
        virtual ~Exception() throw();//这个函数不抛出
        virtual const char* what() const throw();
        const char* stackTrace() const throw();
    private:
        void fillStackTrace();//填充站痕迹
        std::string message_;//异常名字
        std::string stack_;//栈痕迹
        
};

#endif  /*EXCEPTION_H_*/
