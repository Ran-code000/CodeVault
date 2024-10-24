#include <iostream>
#include <vector>
#include <cmath>

struct node
{
    int a, b, c;
    int sum;
}temp;

int main()
{
    int n;
    std::cin >> n;

    std::vector<node> vec;

    for(int i = 0; i < n; i++)
    {
        std::cin >> temp.a >> temp.b >> temp.c;
        temp.sum = temp.a + temp.b + temp.c;
        vec.push_back(temp);
    }

    int cnt = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = i + 1; j <= vec.size(); j++)
        {
            if(abs(vec[i].a - vec[j].a) <= 5 && abs(vec[i].b - vec[j].b) <= 5 
            && abs(vec[i].c - vec[j].c) <= 5 && abs(vec[i].sum - vec[j].sum) <= 10)
            {
                cnt++;
            }
        }
    }

    std::cout << cnt << std::endl;

}