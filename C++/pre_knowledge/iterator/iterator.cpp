# include <iostream>
# include <string>
# include <vector>
# include <algorithm>

void print(const std::vector<std::string> &names)
{
    for(const auto &name : names)
    {
        std::cout << name << "\n";
    };

    std::cout << "\n\n";
}

int main()
{
    std::vector<std::string> names;

    names.push_back("Hello world");
    names.push_back("world world world");
    names.push_back("Sandy");
    names.push_back("Lili");
    names.push_back("John");

    /*std::vector<std::string>::iterator iter = names.begin();

    while(iter != names.end())
    {
        std::cout << *iter << "\n";
        ++iter;
    }*/
    print(names);

    names.insert(names.begin()+2,"Mark");
    names.erase(names.begin()+1);

    std::sort(names.begin(),names.end());

    print(names);


    return 0;
}