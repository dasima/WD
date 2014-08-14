#include "text_corrector.h"
#include "query_server.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    QueryServer server(InetAddress(8080), "in.txt");
    server.start();

    /*
    TextCorrector text("in.txt");
    cout << text.editDistance(argv[1], argv[2]) << endl;
    */
    
    return 0;
}
