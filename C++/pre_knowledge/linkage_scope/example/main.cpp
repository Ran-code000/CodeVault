# include "header.h"
# include <iostream>

extern unsigned short thatnum;
static bool printMe = false;

int main()
{
    unsigned short mainnum = 10;

    std::cout << mainnum << "! is equal to " << returnFactorial(mainnum) << "\n\n";
    std::cout << thatnum << "! is equal to " << returnFactorial(thatnum) << "\n\n";
    std::cout << headernum << "! is equal to " << returnFactorial(headernum) << "\n\n";

    return 0;
}