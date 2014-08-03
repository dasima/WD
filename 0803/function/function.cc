#include <iostream>
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

void test(int i, double d, const string &s)
{
    cout << i << " " << d << " " << s << endl;
}

int main(int argc, const char *argv[])
{
    function<void(const string &, int)> fp;
    fp = bind(&test, 
            _2,//int
            1.88,//double
            _1);//string ----顺序与test中顺序一致
    fp("Tony Parker", 9);//顺序与function中参数顺序一致

    function<void(const string &, int, double)> fp2;
    fp2 = bind(&test, _2, _3, _1);
    fp2("Tony Parker", 9, 1.88);

    function<void(int)> fp3 = bind(&test, _1, 1.88, "Tony Parker");
    fp3(9);
    return 0;
}
