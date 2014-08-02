#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
using namespace std;

int main(int argc, const char *argv[])
{
    int fd;
    try
    {
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd == -1)
            throw runtime_error("socket error");
    }catch(Exception &e)
    {
        cerr << e.what() << endl;
    }
    cout << "try" << endl;
    return 0;
}
