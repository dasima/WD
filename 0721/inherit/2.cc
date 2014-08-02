#include <iostream>
using namespace std;

class Parent{
    public:
        Parent()
            :address_("")
        {}
        void setAddress(const string &address)
        {
            address_ = address;
        }
        void print()
        {
            cout << address_ << endl;
        }
    protected:
       string address_; 
};

class Child:public Parent
{
    public:
        string school_;
        void print()

        {
            Parent::print();
            cout << "child" << endl;
        }
        void setSchool(const string &school)
        {
          //  Parent(address) = address;
            school_ = school;
        }
};

int main(int argc, const char *argv[])
{
    Child d;
    d.setAddress("shenzhen");
    d.print();
    d.school_ = "c1";
    cout << d.school_ << endl;
//    d.set("nanshan", "ccc");
    cout << d.school_ << endl;
    return 0;
}
