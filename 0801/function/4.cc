#include <iostream>
#include <string>
#include <functional>
using namespace std;

void test(int i, double d, const string &s)
{
    cout << "i--- " << i << endl << "d--- " << d << endl << "s--- " << s << endl;
}

int main(int argc, const char *argv[])
{
    //void(*)(int, double, const string&)

    //1. void(*)(int, double)
    function<void(int, double)> fp;
    string s = "Tony Parker";
    fp = bind(&test,
            std::placeholders::_1,
            std::placeholders::_2,
            s);
    fp(9, 1.88);

    //2. void(*)(double, int, const string&)
    function<void(double, int, const string&)> fp2;
    //bind中的参数顺序和test中参数类型顺序要一致，
    //对应本function中第n个参数，用_n
    fp2 = bind(&test,
            std::placeholders::_2,//int,对应的是本function中的第二个参数，所以用_2
            std::placeholders::_1,//double,对应function中的第一个参数,用_1
            std::placeholders::_3);//string,
    fp2(1.88, 9, "Tony Parker");

    //3. void(*)(const string&, int)
    function<void(const string &, int)> fp3;
    double d3 = 1.88;
    fp3 = bind(&test, 
            std::placeholders::_2,//int
            d3,
            std::placeholders::_1);//srting
    fp3( "Tony Parker", 9);

    //4. void(*)(const string &, int, double)
    function<void(const string &, int, double)> fp4;
    fp4 = bind(&test,
            std::placeholders::_2,
            std::placeholders::_3,
            std::placeholders::_1);
    fp4("Tony Parker", 9, 1.88);

    //5.1  void(*)(int)
    function<void(int)> fp5;
    double d = 1.88;
    string s5 = "Tony Parker";
    fp5 = bind(&test,
            std::placeholders::_1,
            d,
            s5);
    fp5(9);

    //5.2 void(*)(const string &)
    function<void(const string &)> fp5_1;
    int i52 = 9;
    double d52 = 1.88;
    fp5_1 = bind(&test, 
            i52,
            d52,
            std::placeholders::_1);
    fp5_1("Tony Parker");

    //6. void(*)()
    function<void()> fp6;
    int i6 = 9;
    double d6 = 1.88;
    string s6 = "Tony Parker";
    fp6 = bind(&test,
            i6,
            d6,
            s6);
    fp6();

    return 0;
}
