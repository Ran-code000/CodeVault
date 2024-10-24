# include <iostream>

class Complex
{
public:
    Complex();
    Complex(double r, double i);
    //Complex complex_add(Complex &d);
    friend Complex operator+(Complex &d);
    
    void print();

private:
    double real;
    double imag;
};

Complex::Complex()
{
    real = 0;
    imag = 0;
}

Complex::Complex(double r, double i)
{
    real = r;
    imag = i;
}

/*Complex Complex::complex_add(Complex &d)
{
    Complex c;

    c.real = real + d.real;
    c.imag = imag + d.imag;

    return c;
}*/

Complex operator+(Complex &c, Complex &d)
{
    return Complex(c.real+d.real,c.imag+d.imag);
}

void Complex::print()
{
    std::cout << "(" << real << ", " << imag << "i)\n";
}

int main()
{
    Complex c1(3,4),c2(5,-10),c3;

    //c3 = c1.complex_add(c2);
    c3 = c1 + c2;
    //c1.operator+(c2)

    std::cout << "c1 = ";
    c1.print();
    std::cout << "c2 = ";
    c2.print();
    std::cout << "c1 + c2 = ";
    c3.print();

    return 0;
}
