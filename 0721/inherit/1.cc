#include <iostream>
using namespace std;

class Parent{
    public:
       string address_; 
};

class Child:public Parent
{
    public:
        string school_;
};

int main(int argc, const char *argv[])
{
    Child d;
    d.address_ = "shenzhen";
    d.school_ = "c1";
    return 0;
}
