#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int n, x;
    std::cin >> n >> x;

    std::string str;
    for(int i = 1; i <= n; i++)
    {
        str += std::to_string(i);
    }

    int cnt = std::count(str.begin(), str.end(), std::to_string(x)[0]);
    //std::count函数的第三个参数期望得到一个和容器内元素相同类型的值。因此，(char)x可能不会得到预期结果，
    //因为x是一个整数，直接转换为char类型可能不会转换为数字x对应的字符。
    //例如，如果x = 2，(char)x实际上会转换为ASCII值为2的字符，而不是字符'2'

    std::cout << cnt;

    return 0;
}