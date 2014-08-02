#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <pthread.h>
using namespace std;

class Singleton{
    public:
        static Singleton *getInstance()
        {
            //用pthread_once保证指针被初始化一次
            //只产生一个实例
            pthread_once(&once_, &initInstance);
            return pInstance_;
        }
        static void initInstance()
        {
            //注册销毁函数
            ::atexit(&destroyInstance);
            pInstance_ = new Singleton;
        }
        static void destroyInstance()
        {
            cout << "destroy" << endl;
            delete pInstance_;
        }

    private:
        Singleton(){};
        Singleton(const Singleton &);
        void operator=(const Singleton &);
        static Singleton *pInstance_;
        static pthread_once_t once_;
};

//这里是定义
Singleton *Singleton::pInstance_ = NULL;
pthread_once_t Singleton::once_ = PTHREAD_ONCE_INIT;

int main(int argc, const char *argv[])
{
    Singleton *p1, *p2;
    p1 = Singleton::getInstance();
    p2 = Singleton::getInstance();

    cout << p1 << endl << p2 << endl;
    return 0;
}
