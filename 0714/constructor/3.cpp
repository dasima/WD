#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Test
{
    public:
        Test(const string &name)
            :name_(name)
        {
            //这里修改语句不合法:
           // name_ = name;
        }
    private:
        const string name_;
};
int main(int argc, const char *argv[])
{
   // Test t;//对象要初始化
    Test t("hello");
    return 0;
}
