C++ 标准库中的 stack 是一个容器适配器，提供了以 LIFO (后进先出)顺序存储元素的功能
它通常是基于 deque 或 vector 实现的

1. 包含头文件
#include <iostream>
#include <stack>
所有 stack 的使用都需要包含 <stack> 头文件

2. 创建 stack
stack<int> stack1; // 使用默认的底层容器（通常是 deque）
stack<int, vector<int>> stack2; // 使用 vector 作为底层容器

3. 基本操作
push: 向栈顶添加元素
pop: 移除栈顶元素
top: 访问栈顶元素
empty: 检查栈是否为空
size: 获取栈中的元素数量

4. 示例代码
#include <iostream>
#include <stack>

int main() {
    // 创建一个空的栈
    stack<int> stack;

    // 向栈顶添加元素
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 访问栈顶元素
    cout << "Top element: " << stack.top() << endl; // 输出 30

    // 栈的大小
    cout << "Stack size: " << stack.size() << endl; // 输出 3

    // 移除栈顶元素
    stack.pop();

    // 再次访问栈顶元素
    cout << "Top element after pop: " << stack.top() << endl; // 输出 20

    // 检查栈是否为空
    if (stack.empty()) {
        cout << "Stack is empty" << endl;
    } else {
        cout << "Stack is not empty" << endl; // 输出 Stack is not empty
    }

    // 再次移除所有元素
    stack.pop();
    stack.pop();

    // 最后检查栈是否为空
    if (stack.empty()) {
        cout << "Stack is empty" << endl; // 输出 Stack is empty
    }

    return 0;
}

5. 使用自定义底层容器
标准库的 stack 允许使用自定义的底层容器，只要它支持以下操作：
empty
size
back
push_back
pop_back
例如，使用 vector 作为底层容器：

#include <iostream>
#include <stack>
#include <vector>

int main() {
    // 使用 vector 作为底层容器
    stack<int, vector<int>> stack;

    // 向栈顶添加元素
    stack.push(100);
    stack.push(200);
    stack.push(300);

    // 访问栈顶元素
    cout << "Top element: " << stack.top() << endl; // 输出 300

    // 移除栈顶元素
    stack.pop();

    // 再次访问栈顶元素
    cout << "Top element after pop: " << stack.top() << endl; // 输出 200

    return 0;
}

6. 常用应用示例
括号匹配检查器
#include <iostream>
#include <stack>
#include <string>

bool isValidParentheses(const string& s) {
    stack<char> stack;
    for(char c : s){
        if(c == '(' || c == '{' || c == '[') stack.push(c);
        else{
            if(stack.empty()) return false;
            if((c == ')' && stack.top() != '(') || (c == ']' && stack.top() != '[') || (c == '}' && stack.top() != '{'))
                return false;
            stack.pop();
        }
    }
    return stack.empty();
}

int main() {
    string s = "{[()]}";
    if (isValidParentheses(s)) {
        cout << "Valid parentheses!" << endl;
    } else {
        cout << "Invalid parentheses!" << endl;
    }
    return 0;
}

反转字符串
#include <iostream>
#include <stack>
#include <string>

string reverseString(const string& s) {
    stack<char> stack;
    for(char c : s) stack.push(c);
    string res;
    while(!stack.empty()){
        res += stack.top();
        stack.pop();
    }
    return res;
}

int main() {
    string s = "hello";
    cout << "Original string: " << s << endl;
    cout << "Reversed string: " << reverseString(s) << endl;
    return 0;
}
