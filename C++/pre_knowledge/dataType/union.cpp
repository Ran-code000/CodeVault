# include <iostream>

union mima
{
    unsigned long birthday;
    unsigned short ssn;
    const char* pet;
};

int main()
{
    mima mima_1;
    mima_1.birthday = 20050710;
    std::cout << mima_1.birthday << std::endl;

    mima_1.pet = "dingding";
    //在 C++ 中，字符串常量是 const char[] 类型，意味着它们是只读的。尝试将它们赋给一个非const的char*指针是不安全的
    std::cout << mima_1.pet << std::endl;
    std::cout << mima_1.birthday << std::endl;

    return 0;
}