#include "queue.h"
#include <pthread.h>
using namespace std;

class MutexLock
{
    public:
        MutexLock()
        {
            if(pthread_mutex_init(&lock_))
            {
                throw runtime_error("fail");
            }   

        }
        ~MutexLock()
        {
            if(pthread_mutex_destroy(&lock_))
            {
                throw runtime_error("destroy fail");
            }
        }

    private:
        pthread_mutex_t lock_;

};

int main(int argc, const char *argv[])
{
    
    return 0;
}
