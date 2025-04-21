## 括号排序

```cpp

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
  int n;
  cin >> n;
  while (n--)
  {
    string s;
    cin >> s;

    stack<char> stk;
    
    int f1 = 1, f2 = 1;
    for (size_t i = 0; i < s.length(); i++)
    {
      if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        f1 = 0, st.push(s[i]);
      else if ((s[i] == ')' && !st.empty() && st.top() == '(') ||
               (s[i] == '}' && !st.empty() && st.top() == '{') ||
               (s[i] == ']' && !st.empty() && st.top() == '['))
      {
        f2 = 0, st.pop();
      }
      else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        f2 = 0;
    }
    if (st.empty() && !f1 && !f2)
      cout << "Yes\n";
    else if (f1 && f2)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}

```