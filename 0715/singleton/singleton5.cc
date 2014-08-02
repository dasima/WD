#include <iostream>
#include <string>
#include <vector>
#include "mutual.h"
using namespace std;

class Singleton
{
    public:
        static Singleton *getInstance()
        {
            if(pInstance_ == NULL)
            {
                mutex_.lock();
                if(pInstance_ == NULL)
                {
                    sleep(1);
                    pInstance_ = new Singleton;
                }
                mutex_.unlock();
            }
            return pInstance_;
        }
    private:
        Singleton(){}
        static Singleton *pInstance_;
        static Mutex mutex_;//类中的这个static只是声明
};
Singleton *Singleton::pInstance_ = NULL;
Mutex Singleton::mutex_;//还需要在类外定义
void *threadFunc(void *arg)
{
    Singleton *s = Singleton::getInstance();
    cout << s << endl;
    return NULL;
}
int main(int argc, const char *argv[])
{
    vector<pthread_t> vec(10);
    for(vector<pthread_t>::iterator it = vec.begin(); it != vec.end(); ++it){//it是个对象，只是具有指针的特性
        pthread_create(&*it, NULL, threadFunc, NULL);//这里不包含pthread头文件也可以 
    }

    for(vector<pthread_t>::iterator it = vec.begin(); it != vec.end(); ++it){
        pthread_join(*it, NULL);    
    }

    return 0;
}
