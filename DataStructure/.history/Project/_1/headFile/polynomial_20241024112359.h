#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include <QString>

class Polynomial {
public:
    Polynomial();
    void add_A_Term(double coefficient, int exponent);
    std::string from_Terms_to_String();
    void from_String_to_Terms(const std::string& str);
    Polynomial add(const Polynomial& other) const;
    Polynomial subtract(const Polynomial& other) const;
    Polynomial multiply(const Polynomial& other) const;
    Polynomial derivative() const;
    double evaluate(double x) const;
    void removeSpace(std::string& polynomial);
private:
    struct Term {
        double coefficient;
        int exponent;
        Term(double c, int e) : coefficient(c), exponent(e) {}
    };
    std::vector<Term> terms;
    void simplify();
};

#endif
