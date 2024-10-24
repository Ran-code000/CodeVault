 <cmath> 或 <math.h>
这个头文件包含了一系列的数学函数，适用于浮点数学运算
这其中包括了三角函数,指数和对数函数,幂函数,开方函数,绝对值函数等

常用函数：
pow(x, y): 计算x的y次幂。
sqrt(x): 计算x的平方根。
sin(x), cos(x), tan(x): 分别计算x的正弦、余弦、正切值。
asin(x), acos(x), atan(x): 计算x的反正弦、反余弦、反正切值。
exp(x): 计算e的x次幂。
log(x): 计算x的自然对数。
log10(x): 计算x的以10为底的对数。
fabs(x): 计算x的绝对值。


示例代码：

#include <iostream>
#include <cmath> // 使用cmath头文件

int main() {
    double x = 9.0, y = 0.5;
    // 幂函数和开方函数
    std::cout << "sqrt(" << x << ") = " << sqrt(x) << std::endl;
    std::cout << "pow(" << x << ", " << y << ") = " << pow(x, y) << std::endl;

    // 三角函数
    double angle = M_PI / 4; // M_PI是cmath中定义的π值
    std::cout << "cos(" << angle << ") = " << cos(angle) << std::endl;

    // 指数和对数函数
    std::cout << "exp(1) = " << exp(1) << std::endl; // e^1
    std::cout << "log(" << x << ") = " << log(x) << std::endl; // 自然对数
    std::cout << "log10(" << x << ") = " << log10(x) << std::endl; // 以10为底的对数

    // 绝对值函数
    double z = -5.5;
    std::cout << "fabs(" << z << ") = " << fabs(z) << std::endl;

    return 0;
}