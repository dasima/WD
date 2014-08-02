#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *const的保护语义与非const返回值的修改语义发生冲突:
 *
 */
char &get_reference(const string &name)
{
    return name;
}
int main(int argc, const char *argv[])
{
    string name = "hello";
    get_reference(name) = 'e';
    cout << name << endl;
    return 0;
}
