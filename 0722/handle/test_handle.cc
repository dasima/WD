#include "handle.h"
#include "animal.h"
#include <vector>
using namespace std;

int main(int argc, const char *argv[])
{
    vector<Handle> vec;

    Cat c;
    Dog d1, d2, d3;
    Bear b1, b2;

    vec.push_back(c);
    vec.push_back(d1);
    vec.push_back(d2);
    vec.push_back(d3);
    vec.push_back(b1);
    vec.push_back(b2);

    for(vector<Handle>::iterator it = vec.begin(); it != vec.end(); ++it){
        (*it) -> display();
    }
    return 0;
}
