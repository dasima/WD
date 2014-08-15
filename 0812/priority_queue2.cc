#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, const char *argv[])
{
    priority_queue<int, vector<int>, greater<int> > q;
    q.push(12);
    q.push(15);
    q.push(9);
    while(!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}
