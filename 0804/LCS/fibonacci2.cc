#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

using namespace std;

//memo数组用来存放记录
uint64_t memo[1000];
//g_count_用来统计函数执行的次数
uint32_t g_count_ = 0;//uint32是无符号32位整型，是一个确定的类型
uint64_t fabonac(uint32_t n)
{
    ++g_count_;
    if(n == 0 || n == 1)
        return 1;
    else
    {
        if(memo[n] != -1)//这里记录不为-1，直接返回，提高执行效率
            return memo[n];
        else
        {
            memo[n] = fabonac(n-1) + fabonac(n-2);
            return memo[n];
        }
    }
}

int main(int argc, const char *argv[])
{
    memset(memo, -1, sizeof memo);
    cout << fabonac(atoi(argv[1])) << endl;
    cout << g_count_ << endl;
    return 0;
}
