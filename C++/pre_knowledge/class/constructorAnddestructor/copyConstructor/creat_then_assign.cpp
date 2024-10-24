# include <iostream>

class Myclass
{
public:
    Myclass(int *p);
    ~Myclass();

    Myclass &operator=(const Myclass &rhs);
    void print()

private:
    int *ptr;
};

Myclass::Myclass(int *p)
{
    ptr = p;
}

Myclass::Myclass()
{
    delete ptr;
}

Myclass &Myclass::operator=(const Myclass &rhs)
//a = b,此时=为a对象的一个方法
{
    if(this != &rhs)
    {
        delete ptr;

        ptr = new int;
        *ptr = *rhs.ptr;
        //得到两个指针指向不同地址，但值相同
    }else
    {
        std::cout << "赋值号两边相同头，不做处理！！\n";
    }

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

    ob1.print();
    ob2.print();

    ob2 = ob1;

    ob1.print();
    ob2.print();

    return 0;
}