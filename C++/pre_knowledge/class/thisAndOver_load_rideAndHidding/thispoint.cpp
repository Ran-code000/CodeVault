# include <iostream>

class Human
{
    char name;
    //Human(char initname);
    Human(char name);
};

/*Human::Human(char initname)
{
    name = initname;
}*/

Human::Human(char name)
{
    this -> name = name;
    //当你创建一个对象的实例并调用其成员函数时，this 指针就会指向这个实例的内存地址
}

int main()
{
    return 0;
}