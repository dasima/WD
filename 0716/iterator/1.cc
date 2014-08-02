#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    //初始化为空，追加
    vector<string> vec;
    vec.push_back("baidu");
    vec.push_back("google");
    vec.push_back("bing");

    cout << "print vec: " << endl;
    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << endl;    
    }

    //指定容器初始大小
    vector<string> vec2(5);
    for(vector<string>::size_type ix = 0; ix != 5; ++ix)
        vec2[ix] = "yahoo";
    for(vector<string>::iterator it = vec2.begin(); it != vec2.end(); ++it){
        cout << *it << endl;    
    }

    //指定容器初始化大小和初始值
    vector<string> vec3(5, string("jd"));
    for(vector<string>::iterator it = vec3.begin(); it != vec3.end(); ++it){
        cout << *it << endl;    
    }

    //一个容器去初始化另一个容器
    vector<string> vec4(vec);
    for(vector<string>::iterator it = vec4.begin(); it != vec4.end(); ++it){
        cout << *it << endl;    
    }

    //用一对迭代器范围去初始化容器
    vector<string> vec5(vec.begin(), vec.end());
    for(vector<string>::iterator it = vec5.begin(); it != vec5.end(); ++it){
        cout << *it << endl;    
    }
    return 0;
}
