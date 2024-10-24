# include <iostream>
# include <iomanip>

/*使用（std::cout << std::fixed << std::setprecision(6);）这行代码的原因：
std::cout 默认情况下不保证精确显示 double 值，
而是根据其内部的设置（诸如精度和格式标志）来格式化输出。
（例如 3.999999 四舍五入到了 4）*/

void process(double c, int d)
{
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "您先输入的" << c << "后输入的" << d << std::endl;
}

void process(int c,double d)
{
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "您先输入的" << c << "后输入的" << d << std::endl;
}


int main()
{
    int a;
    double b;

    std::cout << "请输入一个小数和一个整数(格式为x.x x) : ";
    std::cin >> b >> a;
    process(b,a);

    std::cout << "请输入一个整数和一个小数(格式为x x.x) : ";
    std::cin >> a >> b;
    process(a,b);

    return 0;
}