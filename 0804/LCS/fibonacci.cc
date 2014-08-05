#include <iostream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

uint32_t g_count_ = 0;//uint32是无符号32位整型，是一个确定的类型
uint64_t fabonac(uint32_t n)
{
    ++g_count_;
    if(n == 0 || n == 1)
        return 1;
    else
        return fabonac(n-1) + fabonac(n-2);
}

int main(int argc, const char *argv[])
{
    cout << fabonac(atoi(argv[1])) << endl;
    cout << g_count_ << endl;
    return 0;
}
