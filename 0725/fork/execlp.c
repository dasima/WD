#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    printf("running ps as system\n");

    //结论是:
    //占用内存的时候 内存区域两端值不确定 所以会提示 需要两边哨兵 站岗. 说白了就是初始化! 
    //execlp("ps", "ps", "aux", 0);

    /*
    更改方法.把0 改成 (char *)0  即可 , 或者0改成NULL就不会有警告了,*/
  //  execlp("ps", "ps", "aux", (char*)0);
    execlp("ps", "ps", "aux", NULL);
    printf("Done\n");
    return 0;
}
