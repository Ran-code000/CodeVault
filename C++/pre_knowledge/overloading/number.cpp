# include <iostream>

void squareNum(int num)
{
    num*=num;
    std::cout << "该数字的平方为 : " << num << std::endl;
}

void mutiplyNum(int num1 , int num2)
{
    int mtp = num1 * num2;
    std::cout << "两数的乘积为 : " << mtp << std::endl;
}

void addNum(int numa , int numb , int numc)
{
    int ad = numa + numb + numc;
    std::cout << "三数的和为 : " << ad << std::endl;
}

int main()
{
    int num;
    std::cout << "请输入一个数字 : ";
    std::cin >> num ;

    squareNum(num);

    int num1,num2;
    std::cout << "请输入两个数字(格式为x x) : ";
    std::cin >> num1 >> num2;

    mutiplyNum(num1 , num2);

    int numa,numb,numc;
    std::cout << "请输入三个数字(格式为x x x): ";
    std::cin >> numa >> numb >> numc;

    addNum(numa , numb , numc);

    return 0;
}