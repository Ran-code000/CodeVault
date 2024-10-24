# include <iostream>

class Demo
{
private:
    std::string data;
public:
    Demo(void);

    ~Demo(void);

    void display(void) const
    {
        std::cout << "数据成员的值为 : " << this-> data << std::endl;
    }
};

Demo::Demo(void)
{
    data = "Hello world";
    std::cout << "构造器被调用,创建了对象" << std::endl;
}

Demo::~Demo(void)
{
    std::cout << "析构器被调用,对象被销毁" << std::endl;
}

int main()
{
    Demo mydemo;
    mydemo.display();

    return 0;
}