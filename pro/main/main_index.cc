#include "../include/document.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv[])
{
    Document doc;
    char base[1000];
    getcwd(base, 999);//获取当前路径
    memset(base, '\0', sizeof(base));
    strcpy(base, "../data/");
    doc.readFile(base);
    getcwd(base, 999);
    strcat(base, "/data/index.txt");
    cout << base << endl;

    doc.buildIndex(base);
    return 0;
}
