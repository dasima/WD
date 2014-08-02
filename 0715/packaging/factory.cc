/*
 *改写生产者消费者，封装一个车间类
 *（指明缓冲区大小，生产者数目、消费者数目）
 *
 */

#include "factory.h"
using namespace std;
Factory::Factory(size_t bufferSize,
        size_t produceNum,
        size_t consumeNum)
    :bufferSize_(bufferSize),
    buffer_(bufferSize_),
    produceNum_(produceNum),
    consumeNum_(consumeNum),
    produceThreads_(produceNum_, ProduceThread(buffer_)),
    consumeThreads_(consumeNum_, ConsumeThread(buffer_))
{
}

void Factory::start()
{
    for(vector<ProduceThread>::iterator it = produceThreads_.begin(); it != produceThreads_.end(); ++it)
    {
        it -> start();
    }

    for(vector<ConsumeThread>::iterator it = consumeThreads_.begin(); it != consumeThreads_.end(); ++it)
    {
        it -> start(); 
    }

    for(vector<ProduceThread>::iterator it = produceThreads_.begin(); it != produceThreads_.end(); ++it)
    {
        it -> join();    
    }

    for(vector<ConsumeThread>::iterator it = consumeThreads_.begin(); it != consumeThreads_.end(); ++it)
    {
        it -> join();    
    }
}

