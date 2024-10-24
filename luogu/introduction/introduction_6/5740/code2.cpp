#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// std::map<std::string, std::vector<int>> m 的做法无法实现按输入顺序排序,
// 尝试在向量里存放结构体, 并传入一个 id 来记录输入顺序, 使向量按输入顺序排列
// 自定义 sort 实现排序

struct node
{
    std::string name;
    int a, b, c, id;
}temp;

bool cmp(node a, node b)
{
    int suma = a.a + a.b + a.c;
    int sumb = b.a + b.b + b.c;
    if(suma != sumb)
    {
        return suma > sumb;
    }else
    {
        return a.id < b.id;
    }
}

std::vector<node> vec;

int main()
{
    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        std::cin >> temp.name >> temp.a >> temp.b >> temp.c;
        temp.id = i;
        vec.push_back(temp);
    }
    std::sort(vec.begin(), vec.end(), cmp);
    std::cout << vec[0].name << " " << vec[0].a << " " << vec[0].b << " " << vec[0].c;
    
    return 0;
}