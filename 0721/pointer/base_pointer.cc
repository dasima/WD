#include <iostream>

using namespace std;

class Person
{
    private:
        int id_;
        string name_;
        int age_;
    public:
        Person()
            :id_(-1),
            name_("non"),
            age_(-1)
    {}
        Person(int id, const string &name, int age)
            :id_(id),
            name_(name),
            age_(age)
    {}
        Person(const Person &s)
        {
            id_ = s.id_;
            name_ = s.name_;
            age_ = s.age_;
        }
        Person &operator=(const Person &s)            
        {
            if(this != &s)
            {
                id_ = s.id_;
                name_ = s.name_;
                age_ = s.age_;
            }
            return *this;
        }
        void print(std::ostream &os) const
        {
            os<< "id: " << id_ << " name: " << name_ << " age: " << age_ << endl;
        }
};
class Student : public Person
{
    private:
        string school_;
    public:
        Student()
            :school_("non")
        {}
        Student(int id, const string &name, int age, const string &school)
            :Person(id, name, age), school_(school)
        {}
        Student(const Student &s)
            :Person(s), school_(s.school_)
        {}
        Student &operator=(const Student &s)
        {
            if(this != &s)
            {
                Person::operator=(s);
                school_ = s.school_;
            }
            return *this;
        }
        void print(std::ostream &os) const
        {
            Person::print(os);
            cout << school_ << endl;
        }
};
class Worker : public Person
{
    private:
        string place_;
};
int main(int argc, const char *argv[])
{
    Student s(1, "zhang", 22, "aaa");
    Person *p;
    p = &s;
    return 0;
}
