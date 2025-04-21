#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int res = 0;
int main()
{
    string pre, post;
    cin >> pre >> post;
    for (int i = 0; i < pre.length() - 1; i++)
    {
        string temp;
        temp += pre[i + 1], temp += pre[i];
        if (post.find(temp) != -1)
            res++;
    }
    cout << (int)pow(2, res);
    return 0;
}
