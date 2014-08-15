#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int num_;
    bool operator < (const Node &other) const
    {
        return num_ < other.num_;
    }
};

int main(int argc, const char *argv[])
{
    priority_queue<Node> q;
    Node d1 = {2};
    Node d2 = {5};
    Node d3 = {9};
    q.push(d1);
    q.push(d2);
    q.push(d3);
    while(!q.empty())
    {
        cout << q.top().num_ << endl;
        q.pop();
    }
    return 0;
}
