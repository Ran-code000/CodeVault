# include <iostream>

int main()
{
    unsigned int count;

    std::cout << "输入一个整数 : "; 
    std::cin >> count;

    int *x = new  int[count];
     
    for(int i=0; i< count; i++)
    {
        x[i] = i*i;
        std::cout << "x[" << i << "]的值是" << x[i] <<"\n";
    }

    delete[] x;
    x = nullptr;

    return 0;
}