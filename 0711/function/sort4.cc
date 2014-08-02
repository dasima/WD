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

    bool operator < (const Student &other) const
    {//wrong
        if(score_ != other.score_)
        {
            return score_ < other.score_;
        }
        if(name_ != other.name_)
        {
            return name_ < other.score_;
        }
        return age_ < other.age_;
    }
};
int main(int argc, const char *argv[])
{
    Student stu[3] = 
    {
        {"juelv", 23, 87},
        {"xinge", 24, 78},
        {"shuaihu", 22, 83}
    };
    sort(stu, stu + 3);
    for(int i = 0; i != 3; ++i)
        cout << "name: " << stu[i].name_ << " || score: " << stu[i].score_ << "  || age: " << stu[i].age_ << endl;

    return 0;
}
