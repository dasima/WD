#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Test
{
    public:
        static void draw()
        {
            cout << "static" << endl;
        }
};
int main(int argc, const char *argv[])
{
    /*
     *1,static函数指针类型不含有类名
     *2， &符号不是必要的
     */
//    void (*func)() = &Test::draw;
    void (*func)() = Test::draw;
    func();

    return 0;
}
