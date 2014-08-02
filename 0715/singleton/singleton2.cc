#include <iostream>
#include <string>
#include <vector>
using namespace std;

//把getInstance内部的局部指针设为该类的static指针
//然后每次去检查该static指针是否为NULL
class Singleton
{
    public:
        static Singleton *getInstance()
        {
            if(pInstance_ == NULL)
            {
                pInstance_ = new Singleton;
            }
            return pInstance_;
        }
    private:
        Singleton(){}
        static Singleton *pInstance_;
};
Singleton *Singleton::pInstance_ = NULL;
int main(int argc, const char *argv[])
{
    Singleton *s = Singleton::getInstance();
    cout << s << endl;
    Singleton *s2 = Singleton::getInstance();
    cout << s2 << endl;
    return 0;
}
