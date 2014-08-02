#include <iostream>

using namespace std;

class Person{
    public:
        Person()
            :id_(0),
            name_("non"),
            age_(-1)
        {}
        Person(int id,
                const string &name,
                int age)
            :id_(id),
            name_(name),
            age_(age)
    {}
        void set(int id,
                const string &name,
                int age)
        {
            id_ = id;
            name_ = name;
            age_ = age;
        }
        void print()
        {
            cout << "id : " << id_ << " name: " << name_ << " age : " << age_ << endl;
        }
        virtual ~Person()
        {}
    protected: 
        int id_;
        string name_;
        int age_;
};
class Student : public Person
{
    private:
        string school_;
    public:
        void set(int id,
                const string &name,
                int age,
                const string &school)
        {
            id_ = id;
            name_ = name;
            age_ = age;
            school_ = school;
        }
        void print()
        {
            cout << "student...." << endl;
        }
        void test()
        {
            cout << "test" << endl;
        }
};
int main(int argc, const char *argv[])
{
    Student s;
    Person *p;
    Student *st = &s;
    p = st;

    Person pt;
    p = &pt;
    st = p;

    p = &s;
    st = p;

    return 0;
}
