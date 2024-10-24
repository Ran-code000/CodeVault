# include <iostream>
# include <string>

namespace sysu
{
    namespace student
    {
        std::string name;
        void move()
        {

        }

    }
}

int main()
{
    //using namespace sysu::student;

    sysu::student::name = "Hello world";
    sysu::student::move();

    std::cout << sysu::student::name << std::endl;

    return 0;
}