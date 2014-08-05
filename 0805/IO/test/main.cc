#include "select_poll.h"
#include "socket.h"
#include <signal.h>
using namespace std;

void handler(int fd, char *buf)
{
    cout << "recv data " << buf << endl;
    writen(fd, buf, strlen(buf));
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");

    cout << "11" << endl;

    int fd = getListenFd();
    char buf[1024] = {0};

    SelectPoll sp(fd);
    sp.setSelectCallback(bind(&handler, fd, buf));
    while(1)
    {
        cout << "222" << endl;
        sp.select_wait();
        cout << "after wait..." << endl;
        sp.select_accept();
        cout << "after accept..." << endl;
        sp.select_handle_data();
    }

    /*
    PollPoll pp();
    pp.setPollCallback(test);
    while(1)
    {
        pp.poll_wait();
        pp.poll_accept();
        pp.poll_handle_data();
    }
    */

    return 0;
}
