#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Test
{
    public:
        void set(const string &s)
        {
            s_ = s;
        }
        //const的保护语义与返回值的修改语义冲突
        string &get() const
        {
            return s_;
        }
    private:
        string s_;
};
int main(int argc, const char *argv[])
{
    
    return 0;
}
