#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[])
{
    ofstream os;
    os.open("b.txt");//os会生成一个文件，此处是b.txt
  
    vector<string> vec;
    vec.push_back("bk");
    vec.push_back("sh");
    vec.push_back("naj");
    vec.push_back("dl");
    vec.push_back("gz");

    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it){
        os << *it << endl;    
    }
    return 0;
}
