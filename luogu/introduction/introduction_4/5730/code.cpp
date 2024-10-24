#include <iostream>
#include <string>

int main()
{
    std::string a[10][5] = {
    {"XXX", "X.X", "X.X", "X.X", "XXX"}, //0
    {"..X", "..X", "..X", "..X", "..X"}, //1
    {"XXX", "..X", "XXX", "X..", "XXX"}, //2
    {"XXX", "..X", "XXX", "..X", "XXX"}, //3
    {"X.X", "X.X", "XXX", "..X", "..X"}, //4
    {"XXX", "X..", "XXX", "..X", "XXX"}, //5
    {"XXX", "X..", "XXX", "X.X", "XXX"}, //6
    {"XXX", "..X", "..X", "..X", "..X"}, //7
    {"XXX", "X.X", "XXX", "X.X", "XXX"}, //8
    {"XXX", "X.X", "XXX", "..X", "XXX"}  //9
    };

    int n;
    std::cin >> n;

    std::string str;
    std::cin >> str;

    for(int i = 0; i < 5; i++)
    //整个过程重复5次（因为每个数字图案由5行组成）
    {
        std::string temp;
        for(int j = 0; j < str.size(); j++)
        {
            temp += a[str[j] - '0'][i]; //str[j] - '0'将字符转换成对应的整数值
            if(j != str.size() - 1) 
            {
                temp += ".";
            }
                
        }
        std::cout << temp << std::endl;
    }

    
    
    return 0;
}

/*
1. 实例：斐波那契数列打表

#include <iostream>

// 假设我们需要计算斐波那契数列的前30项
const int MAX_N = 30;
long long fib[MAX_N];

void generateFibonacci() {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < MAX_N; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    generateFibonacci();
    int n;
    std::cin >> n; // 获取用户想要的斐波那契数列的项数
    if (n < MAX_N) {
        std::cout << fib[n] << std::endl;
    } else {
        std::cout << "Out of precomputed range." << std::endl;
    }
    return 0;
}


2. 实例：卡特兰数打表
卡特兰数是组合数学中一个常见的数列，用于各种计数问题，如括号组合、树的形态等。

#include <iostream>

const int MAX_N = 20;
long long catalan[MAX_N];

void generateCatalan() {
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i < MAX_N; ++i) {
        catalan[i] = 0;
        for (int j = 0; j < i; ++j) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }
}

int main() {
    generateCatalan();
    int n;
    std::cin >> n; // 获取用户想要的卡特兰数的项数
    if (n < MAX_N) {
        std::cout << catalan[n] << std::endl;
    } else {
        std::cout << "Out of precomputed range." << std::endl;
    }
    return 0;
}

*/