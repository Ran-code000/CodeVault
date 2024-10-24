#include <iostream>
#include <vector>

std::vector<int> bigSub(std::vector<int> sub, int i);
std::vector<int> bigSum(std::vector<int> sum, std::vector<int> sub);

int main()
{
    int n;
    std::cin >> n;

    /*int sum = 0;
    int sub = 1;
    for(int i = 1; i <= n; i++)
    {
        sub *= i;
        sum += sub;
    }*/

    std::vector<int> sum;
    std::vector<int> sub;
    sum.push_back(0);
    sub.push_back(1);

    for(int i = 1; i <= n; i++)
    {
        sub = bigSub(sub, i);
        sum = bigSum(sum, sub);
    }

    //std::cout << sum;

    for(int i = sum.size() - 1; i >= 0; i--)
    {
        std::cout << sum[i];
    }

    return 0;
}

std::vector<int> bigSub(std::vector<int> sub, int x)
{
    int t = 0;
    std::vector<int> temp;
    for(int i = 0; i < sub.size() || t; i++)
    {
        if(i < sub.size()) t += sub[i] * x;
        //循环中有两个条件, 单独判断
        //若无这句代码将会出现越界访问错误
        temp.push_back(t % 10);
        t /= 10; //进位
    }

    return temp;
}
std::vector<int> bigSum(std::vector<int> sum, std::vector<int> sub)
{
    int t = 0;
    std::vector<int> temp;

    for(int i = 0; i < sum.size() || i < sub.size(); i++)
    {
        if(i < sum.size()) t += sum[i];
        if(i < sub.size()) t += sub[i];
        temp.push_back(t % 10);
        t /= 10; //进位
    }
    if(t) temp.push_back(1);
    //不需要像高精度乘法一样将 t 放在循环条件里 , 因为是高精度加法, 如果 t 最后有值一定是 1

    return temp;
}
