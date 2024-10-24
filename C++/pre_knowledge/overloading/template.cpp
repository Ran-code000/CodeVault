# include <iostream>
# include <string>

template<typename T>
void print(const T &value)
{
    std::cout << "Printvalue : " << value << std::endl;
}

template<typename T>
class Box{
    //定义了一个类模板 Box，它是一个泛型容器，可以存储任何类型的 T
private:
    T content;
    //在类模板的私有部分，声明了一个类型为 T 的成员变量 content，
    //它用于存储 Box 对象将要持有的值
public :
    //Box(const T& content) : content(content) {} // 正确初始化content 并结束构造函数体
    Box(const T&content);

    void print() const { // 正确开始 print 成员函数的声明
        std::cout << "Box contents: " << content << std::endl; // 打印 Box 的内容
    }
};

/*默认的访问修饰符：在 class 中，默认是 private，而在 struct 中，默认是 public。
这意味着，除非你指定，否则在类内部定义的变量和函数是私有的，而在结构中则是公开的*/
template <typename T>
Box<T>::Box(const T& content)
{
    this->content = content;
}

int main()
{
    print(1);
    print(3.14);
    print("Hello world");

    Box<int> intBox(123);
    Box<double> doubleBox(3.14);
    Box<std::string> stringBox("Hello world");

    intBox.print();
    doubleBox.print();
    stringBox.print();

    return 0;
}