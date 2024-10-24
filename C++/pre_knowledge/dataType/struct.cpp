# include <iostream>
# include <string>

struct Human
{
    std::string name;
    std::string id;
    char sex;
}human;

int main()
{
    human.name = "Sandy";
    human.id = "23336055";
    human.sex = 'F';

    std::cout << human.name << std::endl;
    std::cout << human.id << std::endl;
    std::cout << human.sex << std::endl;

    Human* p = &human;
    (*p).name = "hello world";

    std::cout << human.name << std::endl;
    std::cout << p->id << std::endl;
    std::cout << p->sex << std::endl;

    return 0;
}