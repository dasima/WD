#include <list>
#include <vector>
#include <iostream>
using namespace std;
/*
 *list的insert操作，在指定位置前面进行插入
 *看20---23发现it没有变
 */

int main(int argc, const char *argv[])
{
    list<int> mylist;
    list<int>::iterator it;
    //set initial values
    for(int i = 1; i <= 5; ++i)
        mylist.push_back(i);//1 2 3 4 5

    it = mylist.begin();
    ++it;
    cout << *it << endl;//2
    mylist.insert(it, 10);//1 10 2 3 4 5
    cout << *it << endl;//2
    
    --it;
    cout << *it << endl;//10
    vector<int> vec(2, 30);
    mylist.insert(it, vec.begin(), vec.end());//1 30 30 10 2 3 4 5 
    
    cout << *it << endl;//10
    mylist.insert(it, 3, 9);//insert 3 ge 9
    cout << *it << endl;//10

    cout << "mylist contains: " << endl;
    for(it = mylist.begin(); it != mylist.end(); ++it)
        cout << *it << ' ';
    cout << endl;

    return 0;
}
