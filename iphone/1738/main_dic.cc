#include "../include/text_corrector.h"
//#include "../include/cache.h"
#include "../include/query_server.h"
#include "../include/log.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    TextCorrector tc("../data/dic_en.txt", "../data/dic_cn.txt");
    string word;
    while(cin >> word)
    {
        tc.textQuery(word);
        tc.getCache().writeToCacheFile("../data/cache.txt");
    }

    return 0;
}
