# include <iostream>
# include <string>
# include <stdlib.h> //abs
# include <algorithm>

class Rational
{
public:
    Rational(int num, int denom);

    Rational operator+(Rational rhs); //rhs = right and side
    Rational operator-(Rational rhs);
    Rational operator*(Rational rhs);
    Rational operator/(Rational rhs);

   // void print();
    void normalize(); //分数化简

private:
    int numerator; //分子
    int denominator; //分母
    int gcd(int numerator,int denominator); //求最大公约数

    friend std::ostream& operator<<(std::ostream& os,Rational f);
};

Rational::Rational(int num,int denom) : numerator(num) , denominator(denom)
{
    if(denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero!!");
    }
    normalize();
}

int Rational::gcd(int a,int b)
{
    /*while(b > 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }*/

    return b == 0 ? a : gcd(b, a%b);
}

void Rational::normalize()
{
    if(denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    int a = abs(numerator);
    int b = abs(denominator);

    int x = gcd(a,b);

    numerator /= x;
    denominator /= x;

    
}

Rational Rational::operator+(Rational rhs)
{
    int a = numerator;
    int b = denominator;
    int c = rhs.numerator;
    int d = rhs.denominator;

    int e = a*d + b*c;
    int f = b*d;

    return Rational(e,f);
}

Rational Rational::operator-(Rational rhs)
{
    rhs.numerator = -rhs.numerator;

    return operator+(rhs);
}

Rational  Rational::operator*(Rational rhs)
{
    int a = numerator;
    int b = denominator;
    int c = rhs.numerator;
    int d = rhs.denominator;

    int e = a*c;
    int f = b*d;

    return Rational(e,f);
}

Rational Rational::operator/(Rational rhs)
{
    /*int t = rhs.numerator;
    rhs.numerator = rhs.denominator;
    rhs.denominator = t;*/
    std::swap(rhs.numerator,rhs.denominator);

    return operator*(rhs); 
}

/*void Rational::print()
{
    normalize();
    if( numerator % denominator == 0 )
    {
        std::cout << numerator / denominator;
    }else
    {
        std::cout << numerator << "/" << denominator;
    }
}*/

std::ostream& operator<<(std::ostream& os,Rational f)
{
    if(f.numerator == f.denominator) 
    {
        os << "1";
    }else if(f.denominator == 1)
    {
        os << f.numerator;
    }else
    {
        os << f.numerator << "/" << f.denominator;
    }
    
    return os;
}

int main()
{
    Rational f1(18,12);
    Rational f2(3,1);


    /*Rational res = f1 + f2;
    f1.print();
    std::cout << " + " ;
    f2.print();
    std::cout << " = ";
    res.print();
    std::cout << "\n";

    res = f1 - f2;
    f1.print();
    std::cout << " - " ;
    f2.print();
    std::cout << " = ";
    res.print();
    std::cout << "\n";

    res = f1 * f2;
    f1.print();
    std::cout << " * " ;
    f2.print();
    std::cout << " = ";
    res.print();
    std::cout << "\n";

    res = f1 / f2;
    f1.print();
    std::cout << " / " ;
    f2.print();
    std::cout << " = ";
    res.print();
    std::cout << "\n";*/

    std::cout << f1 << " + " << f2 << " = " << f1 + f2 << "\n";
    std::cout << f1 << " - " << f2 << " = " << f1 - f2 << "\n";
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << "\n";
    std::cout << f1 << " / " << f2 << " = " << f1 / f2 << "\n";

    return 0;
}

