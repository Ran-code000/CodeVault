# include <iostream>
# include <string>

//基类和子类，override覆盖方法，overloading重载方法,hidding覆盖方法

class Animal
{
public:
    explicit Animal(std::string theName);
    virtual ~Animal() = default;

    virtual void eat();
    void eat(int eatCount);
    //overloading重载方法，继承之后不能重载，只能在同一个类里面重载
    void sleep();
    void drool();

    std::string getname()
    {
        return name;
    }

protected:
    std::string name;
    
};

class  Pig : public Animal
//此处的public代表继承的方法和属性的访问级别不发生改变
//若为protected,代表把基类的访问级别改为protected(public改，private不变)
//若为private,代表把从基类继承来的所有成员都当成private对待
{
public:
    explicit Pig(std::string theName);
    void eat() override;
    //若为覆盖方法,需要virtual和override关键字*/
    void climb();
    //void eat(int eatCount); 是错的，继承之后不能重载，只能在同一个类里面重载
};

class Turtle : public Animal
{
public:
    explicit Turtle(std::string theName);
    /*void eat();
    //若为覆盖方法,需要virtual和override关键字*/
    void swim();
};

Animal::Animal( std::string theName)
{
    name = theName;
}

Pig::Pig(std::string theName) : Animal(theName)
{

}

Turtle::Turtle(std::string theName) : Animal(theName)
{

}

void Animal::eat()
{
    std::cout << "I'm eating!" << std::endl;
}

void Animal::eat(int eatCount)
{
    std::cout << "I have ate " << eatCount << " apples" << std::endl;
}

void Pig::eat()
{
    Animal::eat(); //little tips
    std::cout << "I'm eating meat!!" << std::endl;
}

/*void Turtle::eat()
{
    Animal::eat(); //little tips
    std::cout << "I'm eating fish!!" << std::endl;
}*/

void Animal::sleep()
{
    std::cout << "I'm sleeping!Don't disturb me!" << std::endl;
}

void Animal::drool()
{
    std::cout << "Don't leave me" << std::endl;
}

void Pig::climb()
{
    std::cout << "I'm climbing!!!" << std::endl;
}

void Turtle::swim()
{
    std::cout << "I'm swimming" << std::endl;
}

int main()
{
    Pig pig("little pig");
    Turtle turtle("little turtle");

    std::cout << "The name of the pig is " << pig.getname() << std::endl;
    std::cout << "The name of the turtle is " << turtle.getname() << std::endl;

    pig.eat();
    turtle.eat();

    //pig.eat(15);
    pig.climb();
    turtle.swim();

    Animal *ptr = new Pig("fat pig");
    ptr->eat();

    delete ptr;
    ptr = nullptr;

    /*std::unique_ptr<Animal> ptr = std::make_unique<Pig>("fat pig");
    ptr->eat();*/
    // 使用unique_ptr来管理Pig对象
    // 当ptr超出作用域时，Pig对象会自动被销毁
    // 不需要手动delete

    getchar();

    return 0;
}
