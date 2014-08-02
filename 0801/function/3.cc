#include <iostream>
#include <string>
#include <functional>

using namespace std;

//c++11新标准

//void(*)()
void test()
{
    cout << "test...." << endl;
}

class Test
{
    public:
        //void (*)()
        static void test_static()
        {
            cout << "test static..." << endl;
        }
        //void (Test::*)()
        void test2()
        {
            cout << "test2 int Test..." << endl;
        }
        //void (Test::*)(int)
        void test3(int i)
        {
            cout << i << "   test3 in Test..." << endl;
        }
};

int main(int argc, const char *argv[])
{
    //void(*)(int, double)
    function<void()> fp;
    fp = test;
    fp();

    fp = Test::test_static;
    fp();

    //fp = Test::test2;
    // error: invalid use of non-static member function ‘void Test::test2()’
    Test t;
    //void(*)(Test*)
    fp = bind(&Test::test2, &t);
    fp();

    //error: ‘std::placeholder’ has not been declared
    //error: no match for call to ‘(std::function<void()>) (int)’
    //fp = bind(&Test::test3, &t, std::placeholder::_1);
    //fp(9);

    //test3----void(*)(int)
    function<void(int)> fp2;
    fp2 = bind(&Test::test3, &t, std::placeholders::_1);
    fp2(9);

    return 0;
}
