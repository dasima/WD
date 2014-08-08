#include "EchoServer.h"
using namespace std;

int main(int argc, const char *argv[])
{
    EchoServer server(InetAddress(8080));
    server.start();
    return 0;
}
