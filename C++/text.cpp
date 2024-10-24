#include <string>
#include <cmath>
#include <stdexcept>
#include <stack>
#include <cctype>
using namespace std;
int precedence(char op){
    switch(op){
        case '+': case '-' : return 1; break;
        case '*': case '/' : return 2; break;
        case '^': return 3;
    }
    return 0;
}
double applyOperator(double a, double b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if(b == 0) throw runtime_error("divide by zero");
            return a / b;
        case '^': return pow(a, b);
        default:
            throw runtime_error("unknown operator");
    }
}
double calculate(const string& expression){
    stack<double> operands; stack<char> operators;
    bool expectOperand = true;
    for(size_t i = 0; i < expression.length(); i++){
        if(isspace(expression[i])) continue;
        if(isdigit(expression[i])){
            double IntegerPart = 0, DecimalPart = 0;
            while(i < expression.length() && isdigit(expression[i])){
                IntegerPart = IntegerPart * 10 + (expression[i] - '0');
                i++;
            }
            if(expression[i] == '.'){
                i++;
                while(i < expression.length() && isdigit(expression[i])){
                    DecimalPart = DecimalPart / 10 + (expression[i] - '0');
                    i++;
                }
                i--;
            }
            double value = IntegerPart + DecimalPart;
            operands.push(value);
            expectOperand = false;
        }else if(expectOperand && expression[i] == '-'){
            i++;
            double IntegerPart = 0, DecimalPart = 0;
            while(i < expression.length() && isdigit(expression[i])){
                IntegerPart = IntegerPart * 10 + (expression[i] - '0');
                i++;
            }
            if(expression[i] == '.'){
                i++;
                while(i < expression.length() && isdigit(expression[i])){
                    DecimalPart = DecimalPart / 10 + (expression[i] - '0');
                    i++;
                }
                i--;
            }
            double value = IntegerPart + DecimalPart;
            operands.push(value * (-1));
            expectOperand = false;
        }else if(expression[i] == '('){
            operators.push(expression[i]);
            expectOperand = true;
        }else if(expression[i] == ')'){
            while(operators.top() != '('){
                double val2 = operands.top(); operands.pop();
                double val1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(applyOperator(val1, val2, op));
            }
            operands.pop();
        }else{
            if(operators.empty() || precedence(expression[i]) > precedence(operators.top())){ operators.push(expression[i]); continue;}
            if(operands.size() < 2) throw runtime_error("not enough operands");
            while(operands.size() >= 2 && !operators.empty() && precedence(expression[i]) <= precedence(operators.top())){
                double val2 = operands.top(); operands.pop();
                double val1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();
                operands.push(applyOperator(val1, val2, op));
            }
            operators.push(expression[i]);
            expectOperand = true;
        }
    }
    while(operands.size() >= 2 && !operators.empty()){
        double val2 = operands.top(); operands.pop();
        double val1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(applyOperator(val1, val2, op));
    }
    if(operands.size() != 1) throw runtime_error("not enough operands");
    if(operators.size() != 0) throw runtime_error("too many operators");
    return operands.top();
}
int main(){
    return 0;
}