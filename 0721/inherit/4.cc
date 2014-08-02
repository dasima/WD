#include <iostream>

using namespace std;

class Parent{
    private:
        string address_;
    public:
        void print()
        {
            cout << "parent" << endl;
        }
        
};

class Child:public Parent
{
    public:
        void set(const string &school)
        {
            school_ = school;
        }
    private:
        string school_;
};
int main(int argc, const char *argv[])
{
    Child d;
    d.set("aaa");
    d.print();
    return 0;
}
