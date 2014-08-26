#include "../include/document.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv[])
{
    /*
     *这里of输出到文件中内容会成功
     *而of2不会成功，因为路径已经发生改变，
     *执行到的语句处路径下不存在一个page.lib文件
     */
    Document doc;
    char base[1000];
    char base2[1000];
    getcwd(base, 999);//获取当前路径
    memset(base, '\0', sizeof(base));
    strcpy(base, "../data/");
    doc.readFile(base);
    getcwd(base, 999);
    getcwd(base2, 999);
    //cout << base << endl;
    strcat(base, "/test/page.lib");
    strcat(base2, "/test/index.txt");
    
    cout << base << endl;
    cout << base2 << endl;

    //ofstream of2(base);
    // of2 << "hellowordl" << ends;
    //doc.buildOffset("page.lib");//这里不会成功执行，因为page.lib不再当前路径下，这里的当前路径是语句执行时的路径
    doc.buildLib(base, base2);
    return 0;
}
