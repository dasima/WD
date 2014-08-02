#ifndef _FACTORY_H_
#define _FACTORY_H_ 
#include "produce_thread.h"
#include "consume_thread.h"
#include <vector>
#include "buffer.h"
class Factory
{
    public:
        Factory(size_t bufferSize_,
                size_t prosuceNum_,
                size_t consumeNum_);
        void start();
    private:
            size_t bufferSize_;
            Buffer buffer_;
            size_t produceNum_;
            size_t consumeNum_;
            std::vector<ProduceThread> produceThreads_;
            std::vector<ConsumeThread> consumeThreads_;

};
#endif  /*_FACTORY_H_*/
