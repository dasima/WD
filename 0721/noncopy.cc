#include <iostream>
using namespace std;
//凡是继承该类的对象，均不可复制和赋值
class NonCopy{
    public:
        NonCopy(){}
        ~NonCopy(){}
    private:
        NonCopy(const NonCopy &);
        void operator=(const NonCopy &);
};
//注意这里采用私有继承
class Test : private NonCopy
{
    
};

int main(int argc, const char *argv[])
{
    Test t;
    Test t2(t);

    Test t3;
    t3 = t;
    return 0;
}
