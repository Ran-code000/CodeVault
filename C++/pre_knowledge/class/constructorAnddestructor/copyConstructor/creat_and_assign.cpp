# include <iostream>

//亲自构造一个副本构造器

/*深复制（Deep Copy）是指在复制对象时，不仅复制对象本身，还包括对象所拥有的所有资源。
在深复制过程中，所有的字段被复制，而且所有指向动态分配内存的指针变量也将重新分配内存，并复制原始对象中的内容。

这种复制方式与浅复制（Shallow Copy）形成对比，浅复制仅复制对象的各个字段，对于指针只复制指针值本身，
不会复制指针指向的数据，这意味着原始对象和副本对象会共享相同的内存资源。

在管理动态资源或指针指向的对象时，深复制尤其重要，因为默认的复制构造函数和赋值运算符通常只会进行浅复制，
这可能会导致诸如双重释放（double free）或内存泄漏（memory leak）等问题。

例如，如果你有一个指向动态分配数组的指针成员变量，并且你进行了浅复制，那么原始对象和副本对象将共享相同的数组。
如果其中一个对象被析构，数组将被释放，而另一个对象将持有一个悬空指针。如果该对象随后尝试访问或释放该数组，程序可能会崩溃。

在C++中，实现深复制通常需要明确编写复制构造函数和重载赋值运算符，手动复制每个需要深复制的成员变量。

*/

class Myclass
{
public:
    Myclass(int *p);
    Myclass(const Myclass &rhs);
    ~Myclass();

    Myclass &operator=(const Myclass &rhs);
    void print();

private:
    int *ptr;
};

Myclass::Myclass(int *p)
{
    std::cout << "进入主构造器\n"; 

    if(p != nullptr)
    {
        ptr = new int(*p); //分配新内存并复制传入的值
    }else
    {
        ptr = new int(0);
    }
    //主构造器应当检查传入的指针是否为 nullptr，避免潜在的空指针解引用错误。

    std::cout << "离开主构造器\n";
}

Myclass::Myclass(const Myclass &rhs)
{
    std::cout << "进入副本构造器\n"; 
    //*this = rhs; 会调用赋值语句重载
    ptr = new int(*rhs.ptr); // 分配新的内存，并复制值，进行深复制
    std::cout << "离开副本构造器\n";
}

Myclass::~Myclass()
{
    std::cout << "进入析构器\n"; 
    delete ptr;
    std::cout << "离开析构器\n";
}

Myclass &Myclass::operator=(const Myclass &rhs)
//a = b,此时=为a对象的一个方法
{
    std::cout << "进入赋值语句重载\n";

    if(this != &rhs)//防止自赋值（self-assignment）
    //当你创建一个对象的实例并调用其成员函数时，this 指针就会指向这个实例的内存地址
    //rhs是一个对类对象的引用，是函数参数，特别是在复制构造函数和赋值运算符中。&rhs就是获取这个引用所指向对象的内存地址
    //this != &rhs 这个比较确保了当前对象（*this）和作为参数传递进来的对象（rhs）不是同一个对象。如果它们的地址相同，
    //那么它们实际上是同一对象。
    {
        delete ptr;
        ptr = new int(*rhs.ptr);
        //得到两个指针指向不同地址，但值相同
    }else
    {
        std::cout << "赋值号两边相同，不做处理！！\n";
    }

    std::cout << "离开赋值语句重载\n";

    return *this;
}

void Myclass::print()
{
    std::cout << *ptr << "\n";
}

int main()
{
    Myclass ob1(new int(1));
    Myclass ob2(new int(2));
    ob2 = ob1;

    ob1.print();
    ob2.print();

    std::cout << "................\n\n";

    Myclass ob3(new int(3));
    Myclass ob4 = ob3;
    ob3.print();
    ob4.print();

    std::cout << "................\n\n";

    Myclass ob5(new int(5));
    ob5 = ob5;
    ob5.print();

    return 0;
}