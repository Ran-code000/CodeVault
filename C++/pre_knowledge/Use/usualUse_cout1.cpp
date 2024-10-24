# include <iostream>
# include <math.h>
# include <iomanip>

int main()
{
    double result = sqrt(3.0);

    for(int i=0; i<=9; i++)
    {
        //cout.precision(i);
        std::cout << std::setprecision(i) << result << std::endl;
    }

    std::cout << "当前的输出精度为："<< std::cout.precision() << std::endl;

    return 0;
}