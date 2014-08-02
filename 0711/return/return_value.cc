#include <iostream>
#include <string>
#include <vector>
using namespace std;

int push()
{
    int num;
    cin >> num;
    if(num == 1)
        return 1;
    else if(num == 2)
        return 2;
    return 0;//所有情况都应有返回值，没有这一句，会有警告。
}
int main(int argc, const char *argv[])
{
    
    return 0;
}
