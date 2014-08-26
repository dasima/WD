#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <echo/exception.h>
using namespace std;

/*
 *读取txt文件，存入字符串。
 *
 */
int main(int argc, const char *argv[])
{
    string doc;
    string docid = "001";
    string url = "www.dasima.com";
    string title = "";//初始化
    string content = "";

    ofstream of;
    ifstream in;

    in.open("11.txt");
    if(!in)
        throw Exception("open file failed");

    string line;
    int i = 1;
    while(getline(in, line))
    {
        if(i == 1)
        {
            title = line;
            i = 0;
        }
        else
            content += line;
    }
    doc = "<doc>\n  <docid>" + docid + "</docid>\n  <url>" + url + "</url>\n   <title>" + title + "   </title>\n    <content>\n" + content + "   </content>\n</doc>\n";

    of.open("01.txt");
    if(!of)
        throw Exception("open file failed");
    of << doc ;

        return 0;
}
