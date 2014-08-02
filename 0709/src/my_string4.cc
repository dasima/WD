#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    string s1 = "tmall";
    s1 += "taobao";
    cout << s1 << endl;

    string s2 = "jd";
    s2 = "suning" + s2;
    cout << s2 << endl;
   
    string s3 = s1 + "okbuy";
    cout << s3 << endl;
    s3 = "dangdang" + s2;//reallocate memory重新分配内存
    cout << s3 << endl;
    //下面的分配是错误的
//    s3 = "guomei" + "yixun" + s1;
    cout << s3 << endl;

    return 0;
}
