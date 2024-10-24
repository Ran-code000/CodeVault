#include <iostream>
#include <cmath>

#define max(a, b, c)  (a > b ? (c > a ? c : a) : (c > b ? c : b))

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    if(a + b <= c || b + c <= a || a + c <= b)
    {
        std::cout << "Not triangle";
        return 0;
    }else
    {
        if(pow(a, 2) + pow(b, 2) == pow(c, 2) || pow(a, 2) + pow(c, 2) == pow(b, 2) || pow(c, 2) + pow(b, 2) == pow(a, 2))
        {
            std::cout << "Right triangle" << "\n";
        }else if(c == max(a, b, c) && pow(a, 2) + pow(b, 2) < pow(c, 2) || b == max(a, b, c) && pow(a, 2) + pow(c, 2) < pow(b, 2) || a == max(a, b, c) && pow(c, 2) + pow(b, 2) < pow(a, 2))
        {
            std::cout << "Obtuse triangle" << "\n";

        }else
        {
            std::cout << "Acute triangle" << "\n";
        }

        if(a == b || a == c || b == c)
        {
            std::cout << "Isosceles triangle" << "\n";

            if(a == b && a == c && b == c)
            {
                std::cout << "Equilateral triangle" << "\n";
            }
        }
    }
    return 0;
}