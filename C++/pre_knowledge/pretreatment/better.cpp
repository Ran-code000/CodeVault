/*宏定义在C++编程中常常被用于定义编译时常量和创建宏函数，但它们不具备类型安全性，并且可能导致预料之外的错误。
使用constexpr、内联函数和模板可以提供类型安全的替代方案，并且使代码在编译时更加可靠。

下面是如何使用constexpr、内联函数和模板来替代宏定义的例子：

1.使用constexpr定义编译时常量：

// 使用宏定义常量
#define PI 3.14159

// 使用constexpr定义常量
constexpr double Pi = 3.14159;
constexpr确保Pi在编译时是常量，并且具有确定的类型。

2.使用内联函数替代宏函数：

// 使用宏定义函数
#define SQUARE(x) ((x)*(x))

// 使用内联函数替代宏函数
inline int square(int x) {
    return x * x;
}
内联函数square与宏SQUARE实现了相同的功能，但是square是类型安全的，并且在调试时能够像普通函数一样被追踪。

3.使用函数模板替代带参数的宏：

// 使用宏定义来实现通用功能
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 使用模板函数替代宏
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
函数模板max可以用于任何可比较的类型，它在使用时会为相应的类型实例化一个新的函数。

4.结合使用constexpr和模板：
某些情况下你可能需要定义依赖于类型的编译时常量，可以结合使用constexpr和模板：

// 使用模板和constexpr结合定义类型相关的常量
template<typename T>
constexpr T pi = T(3.1415926535897932384626433832795);

// 使用模板特化为特定类型提供精确值
template<>
constexpr float pi<float> = 3.14159f;

template<>
constexpr double pi<double> = 3.141592653589793;

int main() {
    // 使用模板常量
    float pi_f = pi<float>;
    double pi_d = pi<double>;
}
在这个例子中，我们定义了一个模板常量pi，它可以根据不同的类型来赋予不同的值。对于float和double类型，我们提供了特化版本，以适应不同的精度需求。

*/