#include <iostream>
#include <vector>
#include <algorithm>

struct node
{
    int a;
    int b;
}temp;

bool cmp(node x, node y)
{
    if(x.a != y.a)
    {
        return x.a < y.a;
    }else
    {
        return x.b < y.b;
    }
}

int main()
{
    int l, m;
    std::cin >> l >> m;

    std::vector<node> vec;

    for(int i = 0; i < m; i++)
    {
        std::cin >> temp.a >> temp.b;
        vec.push_back(temp);
    }

    std::sort(vec.begin(), vec.end(), cmp);

    int min = vec[0].a;
    int max = vec[0].b;
    int sum = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i + 1].a < max)
        {
            if(vec[i + 1].b > max)
            {
                max = vec[i + 1].b;
            }else
            {
                continue;
            }
        }else
        {
            sum += max - min + 1;
            min = vec[i + 1].a;
            max = vec[i + 1].b;
        }
    }

    sum += max - min + 1;

    std::cout << l + 1 - sum << std::endl;

    return 0;
    
}