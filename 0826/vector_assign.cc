#include <iostream>
#include <vector>
/*
 *对容器中元素进行赋值
 *16行为一种方法， 23和29为另一种方法
 */

using namespace std;

int main(int argc, const char *argv[])
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    v1.assign(9, 3);
    for(auto vit = v1.begin(); vit != v1.end(); ++vit)
        cout << *vit << ' ' ;
    cout << endl;

    vector<int>::iterator vit;
    vit = v1.begin() + 1;
    v2.assign(vit, v1.end() - 1);
    for(vit = v2.begin(); vit != v2.end(); ++vit)
        cout << *vit << ' ';
    cout <<  endl;

    int my[] = {9, 8, 7};
    v3.assign(my, my + 3);
    for(vit = v3.begin(); vit != v3.end(); ++vit)
        cout << *vit << ' ';
    cout << endl;

    cout << "size of v1 " << v1.size() << endl;
    cout << "size of v2 " << v2.size() << endl;
    cout << "size of v3 " << v3.size() << endl;
    return 0;
}
