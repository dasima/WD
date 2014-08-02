#include <iostream>
#include <string>
using namespace std;
class Person{
    public:
        Person()
            :id_(0),
            name_(""),
            age_(-1)
    {
    }
        Person(int id, const string name, int age)
            :id_(id),
            name_(name),
            age_(age)
    {
    }
        void print(std::ostream &os) const
        {
            os << "Person -----id:  " << id_ << " name: " << name_ << " age: " << age_ << endl;
        }
    private:
        int id_;
        string name_;
        int age_;
        
};

class Student:public Person
{
    public:
        Student()
            :school_("")
        {}
        Student(int id, const string &name, int age, const string &school)
            :Person(id, name, age), school_(school)
        {
        }
        Student(const Student &s)
            :Person(s), school_(s.school_)
        {
        }
        Student &operator=(const Student &s)
        {
            if(this != &s)
            {
                Person::operator=(s);
                school_ = s.school_;
            }
            return *this;
        }
        void test()
        {
            cout << "test" << endl;
        }
        void print() const
        {
            cout << "Student-----print1" << endl;
            Person::print(cout);
        }
        void print(std::ostream &os) const
        {
            os << "Studetnt-----print" << endl;
            Person::print(os);
        }
    private:
        string school_;
};

class Worker:public Person
{
    private:
    string factory_;
};

int main(int argc, const char *argv[])
{
    Student s1(12, "zhang", 23, "c1");
    s1.print(cout);
    cout << "1111111111" << endl;
    Student s2(s1);
    s2.print();
    cout << "22222222222" << endl;

    Student s3;
    s3 = s1;
    s3.print(cout);
    return 0;
}
