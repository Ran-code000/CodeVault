#include "polynomial.h"
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cmath>

Polynomial::Polynomial(){}

void Polynomial::add_A_Term(double coef, int exp){
    terms.push_back(Term(coef, exp));
}

std::string Polynomial::from_Terms_to_String(){
    simplify();
    std::ostringstream oss;
    bool firstNum = true;
    for(const auto& term : terms) {
        if(term.coefficient != 0) {
            if(!firstNum && term.coefficient > 0) oss << "+";
            if(term.coefficient == 1){
                if(term.exponent == 0) oss << 1;
                else if(term.exponent == 1) oss << "x";
                else oss << "x^" << term.exponent;
            }else if(term.coefficient == -1){
                if(term.exponent == 0) oss << -1;
                else if(term.exponent == 1) oss << "-x";
                else oss << "-x^" << term.exponent;
            }else{
                if(term.exponent == 0) oss << term.coefficient;
                else if(term.exponent == 1) oss << term.coefficient << "x";
                else oss << term.coefficient << "x^" << term.exponent;
            }
            firstNum = false;
        }
    }
    return oss.str();
}

void Polynomial::simplify(){
    std::sort(terms.begin(), terms.end(), [](const Term& a, const Term& b){ return a.exponent > b.exponent;});
    size_t len = terms.size();
    for(size_t i = 0; i < len - 1; i++){
        if(terms[i].exponent == terms[i + 1].exponent){
            terms[i].coefficient += terms[i + 1].coefficient;
            terms.erase(terms.begin() + i + 1);
            i--; len--;
        }
    }
    terms.erase(std::remove_if(terms.begin(), terms.end(),[](const Term& a){
                    return a.coefficient == 0;
                }), terms.end());
    std::sort(terms.begin(), terms.end(), [](const Term& a, const Term& b){ return a.exponent > b.exponent;});
}

Polynomial Polynomial::add(const Polynomial& other) const {
    Polynomial result;
    for(const auto& term : terms) result.add_A_Term(term.coefficient, term.exponent);
    for(const auto& term : other.terms) result.add_A_Term(term.coefficient, term.exponent);
    result.simplify();
    return result;
}

Polynomial Polynomial::subtract(const Polynomial& other) const {
    Polynomial result;
    for (const auto& term : terms) result.add_A_Term(term.coefficient, term.exponent);
    for (const auto& term : other.terms) result.add_A_Term(-term.coefficient, term.exponent);
    result.simplify();
    return result;
}

Polynomial Polynomial::multiply(const Polynomial& other) const {
    Polynomial result;
    for (const auto& term1 : terms)
        for (const auto& term2 : other.terms)
            result.add_A_Term(term1.coefficient * term2.coefficient, term1.exponent + term2.exponent);
    result.simplify();
    return result;
}

Polynomial Polynomial::derivative() const {
    Polynomial result;
    for(const auto& term : terms)
        if(term.exponent != 0) result.add_A_Term(term.coefficient * term.exponent, term.exponent - 1);
    return result;
}

double Polynomial::evaluate(double x) const {
    double result = 0;
    for(const auto& term : terms) result += term.coefficient * std::pow(x, term.exponent);
    return result;
}

void Polynomial::from_String_to_Terms(const std::string& s){
    std::string str = s;
    removeSpace(str);
    size_t len = str.length();
    for(size_t i = 0; i < len;){
        double coff = 0.0; int exp = 0; double sign = 1;
        if(str[i] == '+') sign = 1, i++;
        else if(str[i] == '-') sign = -1, i++;
        if(std::isdigit(str[i])){
            std::string val;
            while(i < len && (std::isdigit(str[i]) || str[i] == '.')) val += str[i], i++;
            coff = sign * std::stod(val);

            if(i < len && str[i] == 'x'){
                i++;
                if(i < len && str[i] == '^'){
                    i++;
                    int _sign = 1; if(i < len && str[i] == '-') _sign = -1, i++;
                    std::string val; while(i < len && std::isdigit(str[i])) val += str[i], i++;
                    exp = _sign * std::stoi(val);
                }else exp = 1;
            }
            terms.push_back({coff, exp});
        }else if(str[i] == 'x'){
            coff = sign;
            i++;
            if(i < len && str[i] == '^'){
                i++;
                int _sign = 1; if(i + 1 < len && str[i + 1] == '-') _sign = -1, i++;
                std::string val; while(i < len && std::isdigit(str[i])) val += str[i], i++;
                exp = _sign * std::stoi(val);
            }else exp = 1;
            terms.push_back({coff, exp});
        }
    }
}
void Polynomial::removeSpace(std::string& polynomial){
    polynomial.erase(std::remove_if(polynomial.begin(), polynomial.end(), ::isspace), polynomial.end());
}

