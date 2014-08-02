#include <iostream>

using namespace std;
//凡是继承该类的对象，都不可以复制和赋值
class NonCopy{
    public:
        NonCopy(){}
        virtual ~NonCopy(){}
    private:
        NonCopy(const NonCopy &){}
        NonCopy &operator=(const NonCopy &){}
        
};
class Test:private NonCopy
{
    
};
int main(int argc, const char *argv[])
{
    Test t1;
    Test t2(t1);
    return 0;
}
