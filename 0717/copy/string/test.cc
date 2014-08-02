#include "string.h"

int main(int argc, const char *argv[])
{
    String s1("hh");//直接初始化
    s1.debug();

    String s2 = s1;//复制初始化
    s2.debug();
    return 0;
}
