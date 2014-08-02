#include <iostream>
#include <vector>

using namespace std;
struct Exmpl{
    public:
        Exmpl()
        {
            cout << "Exmpl()" << endl;
        }
        Exmpl(const Exmpl &exm)
        {
            cout << "Exmpl(const Exmpl& exm)" << endl;
        }
        Exmpl& operator=(const Exmpl& exm)
        {
            cout << "operator=(const Exmpl&)" << endl;
        }
        ~Exmpl()
        {
            cout << "~Exmpl()" << endl;
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
    cout << "&&&&&&&&&&" << endl;
    func1(exm);
    cout << "------------" << endl;

    func2(exm);
    cout << "..........." << endl;
    exm = func3();
    cout << "@@@@@@@@@@@@" << endl;

    Exmpl *p = new Exmpl;
    cout << "???????" << endl;
    std::vector<Exmpl> evec(3);
    cout << "########" << endl;
    delete p;

    cout << "$$$$$$$$$$" << endl;
    return 0;
}
