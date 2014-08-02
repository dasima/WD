#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
void *pthread_func(void *arg)
{
    printf("test...\n");
    /*
     *pthread_detach函数当参数中的线程退出时，立即释放资源
     */
    //pthread_detach(pthread_self());
    pthread_t tid;
    tid = pthread_self();//获取调用线程的ID，和跑thread_create的ID一样
    printf("tid --- %u\n", (unsigned int)tid);
    /*
     * 下面有三种用法1，pthread_exit(NULL)---0
    *2, pthread_exit((void*)9)----9
    *3, 没有这个函数，因为func函数退出时pthread_create函数就会退出
    *此时输出结果为一个数，
    */
    //pthread_exit(NULL);
    /*
     * 该函数可以在退出线程时接收一个线程传给的值，如下面的100，
     */
    pthread_exit((void*)100);

}
int main(int argc, const char *argv[])
{
    pthread_t tid;
    int pp;
    /*
     * pthread_creat创建线程，
     * 线程通过调用函数pthread_func开始执行。
     * 调用pthread_exit函数，
     * 或者func函数结束，该create函数结束
     */
    pp = pthread_create(&tid, NULL, pthread_func, NULL);
    printf("%d\n", pp);//0
    printf("%u\n", (unsigned int)tid);//创建的线程ID
    int status;
    /*
     * join接收线程提供给exit函数的值，为status
     */
    pthread_join(tid, (void**)&status);
    printf("pthread exit code --- %d\n", status);
    
    return 0;
}
