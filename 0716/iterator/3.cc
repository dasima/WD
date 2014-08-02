#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Test
{
    public:
        Test(){}
    private:
        Test(const Test &);
        Test &operator = (const Test &);
};
int main(int argc, const char *argv[])
{
    vector<Test> vec;
    Test t;
    //添加下面的代码才变异错误
   // vec.push_back();
    return 0;
}
