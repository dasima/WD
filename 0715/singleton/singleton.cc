#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Singleton
{
    /*
     *1,把构造函数设为似有，外面就无法直接生成对象
     *2，在类内部添加函数，生成对象，但是不可行、
     *3，把函数设为static
     *4,此时可生成对象，但是不唯一
     */
    public:
        static Singleton *getInstance()
        {
            Singleton *s = new Singleton;
            return s;
        }
    private:
        Singleton(){}
};
int main(int argc, const char *argv[])
{
    Singleton *s = Singleton::getInstance();
    cout << s << endl;
    Singleton *s2 = Singleton::getInstance();
    cout << s2 << endl;
    return 0;
}
