#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Student
{
    string name_;
    int age_;
}
Student *getStudent()
{
    Student s;
    s.name_ = "zhangsan";
    s.age_ = 20;
    return &s;//wrong
}
Student &getStudent2()
{
    Student s;
    return s;//wrong
}
int main(int argc, const char *argv[])
{
    Student &ps = getStudent();
    return 0;
}
