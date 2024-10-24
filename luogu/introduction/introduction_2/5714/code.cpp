#include <iostream>
#include <cmath>

int main()
{
    double m, h;
    std::cin >> m >> h;

    double bmi = m / pow(h, 2);

    if(bmi >= 18.5 && bmi < 24)
    {
        std::cout << "Normal";
    }else if(bmi < 18.5)
    {
        std::cout << "Underweight";
    }else if(bmi >= 24)
    {
        std::cout << bmi << "\n" << "Overweight";
    }
    return 0;
}