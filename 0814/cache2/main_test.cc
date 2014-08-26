#include "text_corrector.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    TextCorrector text("in.txt");
    string s;
    while(cin >> s)
    {
        text.textQuery(s);
        text.writeCacheFile();
    }
    //这里wirteCacheFile()函数不能正常执行，因为我们都是ctrl+c中断程序的，
    //text.writeCacheFile();
    return 0;
}
