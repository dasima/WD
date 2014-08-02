#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Singleton
{
    public:
        static Singleton *getInstance()
        {
            //pInstance 是一种共享资源
            //因此这里存在竞态问题
            if(pInstance_ == NULL)
            {
                sleep(1);
                pInstance_ = new Singleton;
            }
            return pInstance_;
        }
    private:
        Singleton(){}
        static Singleton *pInstance_;
};
Singleton *Singleton::pInstance_ = NULL;

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
