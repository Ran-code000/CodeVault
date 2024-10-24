/*new和delete是用于动态内存分配和释放的运算符。
new用于在自由存储区（通常是堆）上分配内存，并可选择调用对象的构造函数来初始化该内存。
delete用于释放由new分配的内存，并调用相应对象的析构函数来进行清理*/

# include <iostream>

class Myclass
{
public:
    Myclass(void);
    ~Myclass(void);

};

Myclass::Myclass(void)
{
    std::cout << "\nMyclass constructed\n" << std::endl;
}

Myclass::~Myclass(void)
{
    std::cout << "\nMyclass destoryed\n" << std::endl;
}

int main()
{
    int *singleInt = new int(10);

    std::cout << "singleInt : " << *singleInt << "\nsingleInt address : " << singleInt << std::endl;

    delete singleInt;
    singleInt = nullptr;

    
    int *array = new int[5];

    for(int i=0 ; i<5 ; i++)
    {
        array[i] = i*2;
    }

    for(int i=0 ; i<5 ; i++)
    {
        std::cout << array[i] << " ";
    }

    delete[] array;
    array = nullptr;

    Myclass *myObject = new Myclass;
    
    delete myObject;
    myObject = nullptr;
}