#include <iostream>
#include <vector>
using namespace std;
struct Exmpl
{
    Exmpl()
    {
        cout << "construct..." << endl;
    }
    Exmpl(const Exmpl& exm)
    {
        cout << "const Exmpl &" << endl;
    }
    Exmpl &operator=(const Exmpl &exm)
    {
        cout << "operator(const Exmpl &)" << endl;
    }
    ~Exmpl()
    {
        cout << "deconstruct...." << endl;
    }
};
void func1(Exmpl exm)
{
    
}
void func2(Exmpl &exm)
{
    
}
Exmpl func3()
{
    Exmpl exm;
    return exm;
}
int main(int argc, const char *argv[])
{
    Exmpl exm;
    cout << "1  1  1  1" << endl;
    func1(exm);
    cout << "2  2   2   2" << endl;
    func2(exm);
    cout << "3   3   3   3" << endl;
    exm = func3();
    cout << "4  4   4    4  4" << endl;
    Exmpl *p = new Exmpl;
    cout << "5   5    5    5" << endl;
    vector<Exmpl> vec(3);
    cout << "6  6   6    6  6 " << endl;
    delete p;
    cout << "7  7   7    7    7" << endl;
    return 0;


    
    return 0;
}
