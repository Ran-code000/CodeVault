# include <iostream>

//接口搭配，静态变量

class Pet
{
public:
    Pet(std::string theName);
    ~Pet();

    static int getCount();//接口
    // 只能访问静态成员变量或调用静态成员函数
    //静态方法是全局共享的，其无法访问this指针，因此无法在静态方法里访问非静态的类成员
    //因为非静态的类成员需要隐含的this指针来访问

protected:
    std::string name;

private:
    static int count;//搭配使用
};

class Dog : public Pet
{
public:
    Dog(std::string theName);
};

class Cat : public Pet
{
public:
    Cat(std::string theName);
};

int Pet::count = 0;//让编译器为静态变量count分配内存，将变量初始化
// 静态成员变量定义和初始化，需要在类外进行

Pet::Pet(std::string theName)
{
    name = theName;
    count++;

    std::cout << "One pet born.It's name is " << name << "\n";
}

Pet::~Pet()
{
    count--;
    std::cout << "One pet die" <<'\n';
}

int Pet::getCount()
{
    return count;
}

Dog::Dog(std::string theName) : Pet(theName)
{
    std::cout << name << "'this : " << this << std::endl;
    //生成dog时this指针应该指向dog对象
}

Cat::Cat(std::string theName) : Pet(theName)
{
    std::cout << name << "'this : " << this << std::endl;
    //生成cat时this指针应该指向cat对象
}

int main()
{
    Dog dog("Tom");
    Cat cat("Jerry");

    std::cout << " address : " << &dog << "\n";
    std::cout << " address : " << &cat << "\n";

    std::cout << "\nhave borned " << Pet::getCount() << " Pets" << "\n\n";
    //getCount()是一个静态成员函数,它返回当前的count值,因为它是静态的,所以可以通过类名来调用,而不需要任何对象实例来调用

    {
        Dog dog_2("Tom_2");
        Cat cat_2("Jerry_2");

        std::cout << "\nNow,have borned " << Pet::getCount() << " pets" << "\n\n";
    }//注意花括号必不可少,因为花括号定义了一个作用域，在这个作用域结束时，任何在其中创建的对象都会被销毁

    std::cout << "\nAnd you're back to " << Pet::getCount() << " Pets!!\n\n";

    return 0;
}