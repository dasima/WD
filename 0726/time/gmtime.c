#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//获取当前时间
int main(int argc, const char *argv[])
{
    time_t tt;
    //gmtime
    /*
     * gmtime不能用下面这种，
     * 因gmtime返回值不是%s
     * 而是struct tm *
    time(&tt);
    printf("%s\n", gmtime(&tt));
    */

    //返回的是时间戳
    tt = time(NULL);//time(%tt);
    struct tm *p_tm = gmtime(&tt);
    printf("%4d-%2d-%2d-%2d-%2d-%2d-%2d-%2d-%2d\n", 1900+p_tm->tm_year, 1+p_tm->tm_mon, p_tm->tm_mday, 8+p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec, p_tm->tm_wday, p_tm->tm_yday, p_tm->tm_isdst);

    //ctime
    time(&tt);
    printf("%s\n", ctime(&tt));
    return 0;
}
