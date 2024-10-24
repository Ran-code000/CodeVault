# include <iostream>

/*void xorSwap(int *a,int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}*/

void Swap(int &a, int &b);

int main()
{
    int a = 1;
    int b = 2;

    //法一 : std::swap(a,b);
    //法二 : xorSwap( &a , &b );
    //法三 : 引用传递
    Swap(a,b);

    std::cout << "a的值为" << a << std::endl;
    std::cout << "b的值为" << b << std::endl;


    return 0;
}

void Swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}