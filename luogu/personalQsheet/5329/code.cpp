#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct node
{
    std::string str;
    int id;
};

int main()
{
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<node> vec;
    for(int i = 0; i < n; i++)
    {
        node temp;
        temp.str = s.substr(0, i) + s.substr(i + 1);
        temp.id = i + 1;
        vec.push_back(temp);

    }

    std::sort(vec.begin(), vec.end(), [](const node &a, const node &b){ return a.str < b.str;});

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i].id << " ";
    }
    return 0;
}