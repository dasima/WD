#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student
{
    public:
        Student()
            :name_(""), age_(-1), score_(-1)
        {
        
        }
        Student(const string name,
                int age,
                int score)
                :name_(name), age_(age), score_(score)
        {
        
        }
        void print() const
        {
            cout << name_ << " " << age_ << " " << score_ << endl;
        }
    private:
        string name_;
        int age_;
        int score_;
};
int main(int argc, const char *argv[])
{
    Student *s = new Student("zhang", 23, 98);
    s.print();
    Student *s2 = new Student[9];
    
    return 0;
}
