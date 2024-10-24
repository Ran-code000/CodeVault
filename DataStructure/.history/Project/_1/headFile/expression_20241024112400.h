#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <stack>

class Expression {
public:
    Expression();
    double evaluate(const std::string& expression);
    int getPriority(const char& ch);
    double operatorResult(double a, char op, double b);
    void removeSpace(std::string& expression);
    double DealWith_Number(size_t& start_pos, size_t len, const std::string& str);
    void DealWith_RoundBrackets(size_t& i, std::stack<double>& operands, std::stack<char>& operators);
    void DealWith_Operators(size_t& i, std::stack<double>& operands, std::stack<char>& operators, const std::string& str);
    bool  isOperator(const char& ch);
    std::string Change_Into_ReversePolishNotation(const std::string& s);
    std::string Change_Into_PolishNotation(const std::string& s);
};

#endif
