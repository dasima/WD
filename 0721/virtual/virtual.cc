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
       {}
       Person(int id, const string &name, int age)
           :id_(id),
           name_(name),
           age_(age)
    {}
       Person(const Person &p)
       {
            id_ = p.id_;
            name_ = p.name_;
            age_ = p.age_;
       }
       Person &operator=(const Person &p)
       {
            if(this != &p)
            {
                id_ = p.id_;
                name_ = p.name_;
                age_ = p.age_;
            }
            return *this;
       }
       virtual void print(std::ostream &os)
       {
            os << id_ << "  " << name_ << " " << age_ << endl;
       }
};
class Student : public Person
{
    private:
        string school_;
    public:
        Student()
            :school_("no")
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
        void print(std::ostream &os)
        {
            Person::print(os);
            os << school_ << endl;
        }
};
class Worker:public Person
{
    private:
        string place_;
};
int main(int argc, const char *argv[])
{
    Student s(1, "zhao", 22, "aaaaa");
    Person *p = &s;
    p -> print(cout);
    return 0;
}
