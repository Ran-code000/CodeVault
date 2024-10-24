<complex>此头文件用于复数的数学运算, 它定义了一个模板类complex, 可以用来表示和操作复数
包含 float, long, long double 的具体化

常用函数和操作：
real(c): 返回复数c的实部
imag(c): 返回复数c的虚部 
abs(c): 返回复数c的模 
arg(c): 返回复数c的辐角 
norm(c): 返回复数c的模的平方 
conj(c): 返回复数c的共轭复数
polar(rho, theta): 根据模和辐角创建复数, 

示例代码：

#include <iostream>
#include <complex> // 使用complex头文件
using namespace std;
int main(){
    complex<double> c1(3.0, 4.0); // 创建一个复数3+4i
    complex<double> c2 = polar(5.0, M_PI_4); // 根据模和辐角创建复数

    // 输出复数的实部和虚部
    cout << "c1: " << c1.real() << " + " << c1.imag() << "i" << endl;
    cout << "c2: " << c2.real() << " + " << c2.imag() << "i" << endl;

    // 输出复数的模和辐角
    cout << "abs(c1): " << abs(c1) << endl;
    cout << "arg(c1): " << arg(c1) << endl;

    // 输出复数的共轭
    complex<double> c1_conj = conj(c1);
    cout << "conj(c1): " << c1_conj.real() << " + " << c1_conj.imag() << "i" << endl;

    // 复数的加法
    complex<double> sum = c1 + c2;
    cout << "c1 + c2: " << sum.real() << " + " << sum.imag() << "i" << endl;

    return 0;
}