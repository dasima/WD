#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Test
{
    /*
     *这里编译错误，原因在于test加上了const属性，这使得在test内，无法修改被对象
     */
    public:
        void test() const
        {
            a_ = 9;
        }
    private:
        int a_;
};
int main(int argc, const char *argv[])
{
    Test t;

    return 0;
}
