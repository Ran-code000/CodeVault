# include <iostream>

# define FULL_GAS 85.0

class Car
{
public:
    std::string color;
    std::string engine;
    float gas_tank;
    unsigned int wheel;

    Car(void);
    ~Car(void) = default;
    
    void setColor(std::string col);
    void setEngine(std::string eng);
    void setWheel(unsigned int whe);
    void fill_tank(float liter);
    int running(void);
    void warning(void);
};

//构造器,构造器是用于创建对象时初始化对象的函数
Car::Car(void)
{
    color = "white";
    engine = "V8";
    wheel = 4;
    gas_tank = FULL_GAS;
}

void Car::setColor(std::string col)
{
    color = col;
}

void Car::setEngine(std::string eng)
{
    engine = eng;
}

void Car::setWheel(unsigned int whe)
{
    wheel = whe;
}

void Car::fill_tank(float liter)
{
    gas_tank += liter;

    if(gas_tank > 100) gas_tank = 100;
    
}

int Car::running(void)
{
    std::cout << "我正在以120的时速往前移动,翻过高山,越过黄河........\n" ;
    gas_tank--;
    std::cout << "当前还剩" << 100*gas_tank/FULL_GAS << "%" << "油量！！！\n";

    char i;

    if(gas_tank < 10)
    {
        std::cout << "请问是否需要加满油再行驶？(Y/N)\n";
        std::cin >> i;

        if(toupper(i) == 'Y')
        {
            fill_tank(FULL_GAS);
        }

        if(0 == gas_tank)
        {
            std::cout << "抛锚中.....";
            return 1;
        }

    }

    return 0;
}

void Car::warning(void)
{
    std::cout << "WARNING!" << "还剩" << 100*gas_tank/FULL_GAS << "%" << "油量！！\n"; 
}

int main()
{
    Car mycar;
    while( ! mycar.running() )
    {
        ;
    }

    return 0;
}