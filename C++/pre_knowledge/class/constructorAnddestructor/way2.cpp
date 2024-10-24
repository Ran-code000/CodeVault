# include <iostream>

class Demo
{
private:
    std::string data;
public:
    // 使用 explicit 关键字避免隐式转换
    explicit Demo(std::string initdata) :data(initdata)
    //构造函数初始化列表,初始化列表效率更高，因为它避免了不必要的构造和析构操作
    //如果成员变量是 const 或者引用，那么它们必须在初始化列表中初始化
    {
        std::cout << "构造器被调用!!创建了一个对象" << std::endl;
    };

    ~Demo(void)
    {
        std::cout << "析构器被调用!!!对象被销毁" << std::endl;
    };

    void display(void) const
    //const 表明该成员函数不会修改对象的状态。这意味着，这个函数内部不能修改任何成员变量（除非它们被标记为 mutable）
    {
        std::cout << "数据成员的值为 : " << data << std::endl;
        //将构造函数的参数 data 改名为 initData，这样就不需要在构造函数体中使用 this-> 来区分成员变量和参数了
    }
};

int main()
{
    Demo mydemo("Hello world");
    mydemo.display();

    return 0;
}