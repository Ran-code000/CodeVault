# include <iostream>

class Point
{
private:
    int x , y;
public:
    Point(int a, int b)
    {
        x = a;
        y = b;
    }

    void movePoint(int a, int b)
    {
        x = a;
        y = b;
    }

    void print(void)
    {
        std::cout << "x = " << x <<" y = " << y <<std::endl;
    }

};

int main()
{
    Point point1(10,10); //有一个this指针指向point1的地址
    point1.movePoint(2,2); 
    //movePoint函数的原型应该是void movePoint(Point *this,int a,int b){this->x = a ; this->y = b}
    //其中this参数在c++中是隐含的
    point1.print();

    return 0;
}