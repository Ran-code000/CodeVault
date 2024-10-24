#include <iostream>
#include <vector>
#include <string>
#include <stack>

int main()
{
    std::string s;
    std::vector<std::string> vec;

    while(std::cin >> s && !s.empty())
    {
        vec.push_back(s);
    }
    std::cout << vec.size() << " ";

    s.clear();
    for(const auto str : vec)
    {
        s += str;
    }

    std::stack<bool> stk;
    bool now = false; //设置状态
    for(int i = 0; i <= s.length(); i++)
    //把循环条件写成 <= 而不是 <。因为最后一组数字是不会被判断出来的，所以要故意的“越界一下
    {
        stk.push(s[i] - '0');
        if(s[i] - '0' != now)
        {
            stk.pop();//先弹出
            std::cout << stk.size() << " ";

            while(!stk.empty())
            {
                stk.pop();
            }

            stk.push(s[i] - '0');//后放回
            now = !now;
        }
    }

    //当然，也可以在程序最后输出一次栈的大小
    // 若for 循环中条件改为正常的 i < s.length();
    //则for循环后多写一句 std::cout << stk.size();
    return 0;
}