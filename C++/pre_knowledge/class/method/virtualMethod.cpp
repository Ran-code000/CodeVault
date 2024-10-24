# include <iostream>
# include <string>

//虚方法是可以在派生类中被重写的基类方法。这意味着当通过基类指针或引用调用该方法时，将会调用对象实际类型的方法

class Pet
{
public:
    Pet(std::string theName);

    void eat() const;
    void sleep() const;
    virtual void play() const;

protected:
    std::string name;
};

class Cat : public Pet
{
public:
    Cat(std::string theName);

    void climb() const;
    void play () const override;
};

class Dog : public Pet
{
public:
    Dog(std::string theName);

    void play() const override;
    void bark() const;
};

Pet::Pet(std::string theName)
{
    name = theName;
}

void Pet::eat() const
{
    std::cout << "I'm eating \n";
}

void Pet::sleep() const
{
    std::cout << "I'm sleeping \n";
}

void Pet::play() const
{
    std::cout << "I'm playing \n";
}

Cat::Cat(std::string theName) : Pet(theName)
{
    name = theName;
}

void Cat::play() const
{
    Pet::play();
    std::cout << "I'm playing ball \n";
}

void Cat::climb() const
{
    std::cout << "I'm climbing \n";
}

Dog::Dog(std::string theName) : Pet(theName)
{
    name = theName;
}

void Dog::bark() const
{
    std::cout << "I'm barking \n";
}

void Dog::play() const
{
    Pet::play();
    std::cout << "I'm playing the bone \n";
}

int main()
{
    Pet *cat = new Cat("Tom");
    Pet *dog = new Dog("Bob");

    cat->sleep();
    cat->eat();
    cat->play();

    dog->sleep();
    dog->eat();
    dog->play();

    delete cat;
    cat = nullptr;

    delete dog;
    dog = nullptr;

    return 0;
}