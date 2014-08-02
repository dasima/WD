#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
 *这里采用值拷贝，函数调用是把cout拷贝一份
 *
 */
/*
void print(ostream os)
{
    os << "hi" << endl;
}*/

void print(ostream &os)
{
    os << "hi" << endl;
}
int main(int argc, const char *argv[])
{
    print(cout);

    return 0;
}
