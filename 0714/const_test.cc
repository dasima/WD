#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student
{
    public:
        Student(const string &name,
                int age,
                int score
                )
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }

        void set(const string &name,
                int age,
                int score) 
        {
            name_ = name;
            age_ = age;
            score_ = score;
        }

        void print()
        {
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
        void print() const
        {
            cout << "const: ------------" << endl;
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
    private:
        string name_;
        int age_;
        int score_;
};
int main(int argc, const char *argv[])
{
    Student s1("zhang", 23, 87);
    s1.print();

    Student const s2("li", 29, 78);
//    s2.set("wu", 31, 86);
    s2.print();
    return 0;
}
