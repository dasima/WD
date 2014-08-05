#ifndef _THREAD_H_
#define _THREAD_H_

#include "non_copyable.h"
#include <functional>
#include <pthread.h>

class Thread : private NonCopyable
{
    public:
        typedef std::function<void ()> ThreadFunc;

        Thread();
        //防止可能引发错误的隐式类型转换。
        //explicit 关键字只能应用于类中的 ctor 声明以显式构造对象。
        //通常，建议将所有单参数 ctor (构造函数)标记为 explicit，除非确定需要隐式转换。
        explicit Thread(const ThreadFunc &callback);//
        ~Thread();

        void setCallback(const ThreadFunc &);
        void start();
        void join();
    private:
        static void *threadFunc(void *);//

        pthread_t tid_;
        bool is_started_;
        ThreadFunc callback_;
};

#endif  /*_THREAD_H_*/
