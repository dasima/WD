#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student
{
    string name_;
    int age_;
    float score_;
};
bool cmp(const Student &s1, const Student &s2)
{
    if(s1.score_ < s2.score_)
    {
        return s1.score_ < s2.score_;
    }
    if(s1.name_ < s2.name_ )
    {
        return s1.name_ < s2.name_;
    }
    return s1.age_ < s2.age_;
}
int main(int argc, const char *argv[])
{
    Student stu[3] = 
    {
        {"juelv", 23, 87},
        {"xinge", 24, 78},
        {"shuaihu", 22, 83}
    };
    sort(stu, stu + 3, cmp);
    for(int i = 0; i != 3; ++i)
        cout << "name: " << stu[i].name_ << " || score: " << stu[i].score_ << "  || age: " << stu[i].age_ << endl;

    return 0;
}
