#include <iostream>

int main()
{
    int h1,m1,h2,m2;

    std::cin >> h1 >> m1 >> h2 >> m2;

    int h = h2 - h1;
    int m = m2 - m1;

    if(m < 0)
    {
        h--;
        m += 60;
    }

    std::cout << h << " " << m;

    return 0;
}