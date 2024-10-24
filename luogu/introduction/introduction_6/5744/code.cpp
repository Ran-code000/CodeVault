#include <iostream>
#include <vector>
#include <string>

struct People
{
    std::string name;
    int age;
    int score;
}people;

std::vector<People> vec;

int main()
{
    int n;
    std::cin >> n;

    for(int i = 0; i < n; i++)
    {
        std::cin >> people.name >> people.age >> people.score;
        vec.push_back(people);
    }

    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].score * 1.2 > 600)
        {
            vec[i].score = 600;
        }else
        {
            vec[i].score *= 1.2;
        }
        vec[i].age += 1;

        std::cout << vec[i].name << " " << vec[i].age << " " << vec[i].score << std::endl;
    }
    return 0;
}