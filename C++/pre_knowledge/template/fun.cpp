# include <iostream>
# include <string>

template <class T>
void swap(T &a,T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    int i1 = 100;
    int i2 = 200;

    std::cout << "交换前,i1 = " << i1 << " i2 = " << i2 << "\n";
    swap(i1,i2);
    std::cout << "交换后,i1 = " << i1 << " i2 = " << i2 << "\n";

    std::string s1 = "Hello";
    std::string s2 = "world";

    std::cout << "交换前,s1 = " << s1 << " s2 = " << s2 << "\n";
    swap(s1,s2);
    std::cout << "交换后,s1 = " << s1 << " s2 = " << s2 << "\n";

    return 0;
}