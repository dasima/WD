#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Student
{
    string name_;
    int age_;
    int score_;

    void print(ostream &os)
    {
        os << name_ << " " << age_ << " " << score_ << endl;
    }
};
void print(const Student &s, ostream &os)
{
    os << s.name_ << " " << s.age_ << " " << s.score_ << endl;
}
int main(int argc, const char *argv[])
{
    Student s;
    s.name_ = "decon";
    s.age_ = 37;
    s.score_ = 87;
    //执行下列语句，print打印的是s的变量，相当于print函数与s进行了绑定
    s.print(cout);

    print(s, cout);

    return 0;
}
