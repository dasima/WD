#include "select_poll.h"
#include "poll_poll.h" 
#include "socket.h"
#include <signal.h>
using namespace std;

ReadWrite wr;
Socket sock;
void handler(int fd, char *buf)
{
    printf("recv data %s\n", buf);
    cout << "handler..." << endl;
    wr.writen(fd, buf, strlen(buf));
}

int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");


    int fd = sock.getListenFd();
    char buf[1024] = {0};

    /*
    SelectPoll sp(fd);
    sp.setSelectCallback(bind(&handler, fd, buf));
    while(1)
    {
        sp.select_wait();
        sp.select_accept();
        sp.select_handle_data();
    }
    */

    /*
    PollPoll pp(fd);
    pp.setPollCallback(bind(&handler, fd, buf));
    while(1)
    {
        pp.poll_wait();
        pp.poll_accept();
        pp.poll_handle_data();
    }
    */

    EpollPoll ep(fd);
    while(1)
    {
        epoll_do_wait();
        epoll_do_handle();
    }
    close(fd);


    return 0;
}
