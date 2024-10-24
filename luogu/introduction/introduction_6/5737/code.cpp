#include <iostream>
#include <vector>

bool isLeapyear(int year)
{
    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        return true;
    }else
    {
        return false;
    }
}

int main()
{
    int yearStart,yearEnd;
    std::cin >> yearStart >> yearEnd;

    std::vector<int> v;
    v.reserve((yearEnd-yearStart)/4);

    for(int year = yearStart ; year <= yearEnd ; year++)
    //确保循环中包含了 yearEnd，因为题目要求的是闭区间 [x, y]
    {
        if(isLeapyear(year))
        {
            v.push_back(year);
        }
    }

    std::cout << v.size() << "\n";
    //直接使用 std::vector 的 size() 成员函数来获取闰年个数

    for(const auto &val : v)
    {
        std::cout << val << " "; 
    }

    return 0;
}