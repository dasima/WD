#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<pair<string, int> > vec;

    vec.push_back(make_pair("beijing", 31));
    vec.push_back(make_pair("tianjin", 30));
    vec.push_back(make_pair("shanghai", 31));
    vec.push_back(make_pair("guangzhou", 33));
    vec.push_back(make_pair("chongqing", 35));
    string city = "guangzhou";
    for(vector<pair<string, int> >::iterator it = vec.begin(); it != vec.end(); ++it){
        if(it -> first == city)
        {    cout << city << ":" << it -> second << endl;
            break;
        }
    }
    return 0;
}
