#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_account = 1000;

void *thread_A(void* arg)
{
    int cnt = 0;
    while(1)
    {
       int temp = total_account;
       printf("NO.%d before save money.account equals %d\n", cnt, temp);
       temp += 500;
       sleep(3);
       total_account = temp;
       printf("NO.%d after save money.account equals %d\n", cnt, temp);
       ++cnt;
    }
}
void *thread_B(void* arg)
{
    int cnt = 0;
    while(1)
    {
       int temp = total_account;
       printf("NO.%d before withdraw money.account equals %d\n", cnt, temp);
       temp -= 300;
       sleep(3);
       total_account = temp;
       printf("NO.%d after withdraw money.account equals %d\n", cnt, temp);
       ++cnt;
    }
}
int main(int argc, char* argv[])
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_A, NULL);
    pthread_create(&tid2, NULL, thread_B, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
