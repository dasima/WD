#include "animal.h"
#include <iostream>
#include <map>
#include <stdlib.h>
using namespace std;

Animal::Animal(const string &king)
    :king_(king)
{
}

void Animal::add(const string &city, const string &agent)
{
    group_[city] = agent;
}

string Animal::search(const string &city) const
{
    map<string, string>::const_iterator it = group_.find(city);
    if(it == group_.end())
        return "";
    else
        return it->second;
}

void Animal::run()
{
    cout << "公司 : " << king_ << "倒闭了 " << endl;
    srand(time(NULL));
    for(map<string, string>::iterator it = group_.begin(); it != group_.end(); ++it)
    {
        cout << "公司在 : " << it->first << "城市的代理 " << it->second << "辞职了" << rand() % 3 << "天以前" << endl;
    }
}
