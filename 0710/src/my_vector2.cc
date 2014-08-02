#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;
void trans_string(string &str)//地址传递
{
        for(string::iterator iter = str.begin(); iter != str.end(); ++iter)
        {
           if(isupper(*iter))
              *iter =  tolower(*iter);//tolower返回值是
           else if(islower(*iter))
              *iter =  toupper(*iter);
        }
}
int main(int argc, const char *argv[])
{
    string str;
    while(cin >> str)
    {
        trans_string(str);
    
        cout << str << endl;
    }
    return 0;
}
