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
    Person *p ;
    p = &s;
    //
    p -> set(1, "zhang", 22);
    //p以为自己指向的是Person对象，调用的就是Person的版本
    p -> print();
    //
    p -> test();
    return 0;
}
