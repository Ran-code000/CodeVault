#include "expression.h"

#include <stdexcept>
#include <cctype>
#include <cmath>
#include <algorithm>

Expression::Expression() {}

double Expression::evaluate(const std::string& expression){

    std::string str = expression; //去掉 const 属性，使其能够被 removeSpace 函数修改
    removeSpace(str);
    //操作数栈 operands 和运算符栈 operators：使用栈来处理中缀表达式
    std::stack<double> operands; std::stack<char> operators;
    //expectOperand：跟踪下一个应当是操作数还是运算符。初始时，计算器期望第一个字符是操作数（这里用来特判 1.负数，2.形如 -(表达式) 的情况
    //              ———— 1.负数：较简单，将标识取反即可；
    //                   2.-(表达式) 的情况需要内嵌对括号的处理，但内嵌会和之后正常判断括号的代码重复（代码不简洁且逻辑混乱）），
    //                    所以当为此情况时我们不在处理数字的逻辑里判断，在处理括号里加一个特判（减号还是负号）即可
    //                     ps:特判逻辑 ———— 已知减号是双目运算符，负号是单目运算符，因此判断当弹出左括号后操作数栈中元素的个数：若只有一个则为负号，否则为减号
    size_t len = str.size(); bool expectOperand = true;
    for(size_t i = 0; i < len;){
        //处理数字（三种情况：正数，负数（普通负数，表达式取负数））
        if(std::isdigit(str[i]) || (str[i] == '-' && expectOperand == true)){
            //若为表达式去负数则跳过判断，在括号匹配的逻辑中去特判
            if(i + 1 < len && str[i] == '-' && str[i + 1] == '('){ operators.push(str[i]), i++; continue;}
            //用标志位标记是正数还是普通负数
            int sign = str[i] == '-' ? -1 : 1; if(str[i] == '-') i++; //若为负数标志位取反，指针（这里是索引）后移一位，指向待处理的数字（此时是一个字符串）的字符首位
            operands.push(sign * DealWith_Number(i, len, str)); //注意：乘标志位
            expectOperand = false; //操作数下一个不应该是操作数
        //处理括号
        }else if(str[i] == '('){ //左括号直接入队，且期望下一个是操作数
            operators.push(str[i]), i++;
            expectOperand = true;
        }else if(str[i] == ')'){ //右括号除法弹栈
            DealWith_RoundBrackets(i, operands, operators); //包含基本弹栈逻辑和负表达式逻辑的处理
            expectOperand = false; //右括号后不希望下一个是数字
        //处理除括号外操作符的处理
        }else{
            DealWith_Operators(i, operands, operators, str);
            expectOperand = true;
        }
    }
    //当遍历完表达式后，若运算符栈非空，继续执行栈中运算符的计算，直到栈为空
    while(!operators.empty() && operands.size() >= 2){
        //注意操作数顺序 ———— 前操作数先入栈，后操作数后入栈
        //注意取操作数或操作符后要弹栈
        double val_2 = operands.top(); operands.pop();
        double val_1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        //将计算后的结果压入栈，进行下一层的运算
        operands.push(operatorResult(val_1, op, val_2));
    }
    //如果最终栈中剩下的操作数不是一个（最终的运算结果应该只有一个），或者运算符栈非空（表达式输入格式不正确），则说明表达式无效，抛出异常
    if(operands.size() != 1 && !operators.empty()) throw std::runtime_error("Invaild expression!!!");
    return operands.top(); //返回操作数栈的顶值作为最终结果
}
int Expression::getPriority(const char& ch){
    switch (ch){
    case '+': case'-': return 1;
    case '*': case'/': return 2;
    //括号入栈不是根据操作符优先级，而是遇到左操作符直接入栈，遇到右操作符触发弹栈
    //优先级设置必须小于加减乘除等操作符 ———— 因为括号内需要其他操作符按优先级入栈，但入栈条件是优先级大于栈顶（栈底到栈顶是按优先级不递减的规则排放的）
    case '(': case')': return 0;
    default:
        //输入不规范操作符抛出异常
        throw std::runtime_error("Invaild operator");
    }
}
double Expression::operatorResult(double a, char op, double b){
    switch (op){
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if(b == 0) throw std::runtime_error("My dear user~ Don't fucking divide by zero !!!!!");
        return a / b;
    default:
        //除零异常
        throw std::runtime_error("The operator is not vaild!!!");
    }
}
void Expression::removeSpace(std::string& expression){
    //循环写法
    // size_t len = expression.size();
    //注意每次 erase 后容器结构改变，长度减 1，且指针位置指向删除元素的后一位，但因为长度减 1，索引值偏移，需要 i-- 将指针指回下一个待判断的数字
    // for(size_t i = 0; i < len; i++) if(std::isspace(expression[i])) expression.erase(expression.begin() + i), i--, len--;
    // STL 算法写法
    //remove_if 逻辑删除（实际将删除元素移到容器末尾，返回移动后第一个待删除元素的迭代器），用 erase 彻底删除迭代器范围内的元素
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
}
//处理数字
double Expression::DealWith_Number(size_t& i, size_t len, const std::string& str){
    //循环方法，顺序分别处理整数和小数部分（注意整数通过乘 10 加新数转换；小数通过因子不断除以 10 ———— 为了保证权重正确）
    // double Integer_val = 0, Decimal_val = 0;
    // while(i < len && std::isdigit(str[i])) Integer_val = Integer_val * 10 + (str[i] - '0'), i++;
    // if(i < len && str[i] == '.'){
    //     i++; double d = 0.1;
    //     while(i < len && std::isdigit(str[i])) Decimal_val += d * (str[i] - '0'), d /= 10, i++;
    // }
    // return Integer_val + Decimal_val;
    //用 c++ 库函数转换 ———— e.g. std::stod(), std::stoi(), std::stol(), std::stoll()
    //扩展：std::stod()重载 ———— double stod(const std::string& str, size_t* pos = nullptr);
    //    std::stoi()重载 ———— int stoi(const std::string& str, size_t* pos = nullptr, int base = 10); base（进制） 支持 2 到 36 之间的进制
    //    std::stol(), std::stoll() 与 std::stoi() 类似
    std::string result;
    while(i < len && (std::isdigit(str[i]) || str[i] == '.')) result += str[i], i++;
    return std::stod(result);
}
//处理括号
void Expression::DealWith_RoundBrackets(size_t& i, std::stack<double>& operands, std::stack<char>& operators){
    while(!operators.empty() && operators.top() != '(' && operands.size() >= 2){
        //注意两个操作数的顺序
        double val_2 = operands.top(); operands.pop();
        double val_1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(operatorResult(val_1, op, val_2));
    }
    if(!operators.empty()) operators.pop(); //弹出左括号
    //特判形如 -(表达式) 的情况
    //ps:特判逻辑 ———— 已知减号是双目运算符，负号是单目运算符，因此判断当弹出左括号后操作数栈中元素的个数：若只有一个则为负号，否则为减号
    if(!operators.empty() && operators.top() == '-' && operands.size() == 1){
        double temp = operands.top() * (-1); operators.pop(); //弹出负号，栈顶数字取负
        operands.push(temp);
    }
    i++;
}
//处理操作数
void Expression::DealWith_Operators(size_t& i, std::stack<double>& operands, std::stack<char>& operators, const std::string& str){
    //栈空或优先级大直接入栈（栈排放规则：栈底到栈顶是按优先级不递减的规则排放的）
    if(operators.empty() || (getPriority(str[i]) > getPriority(operators.top()))){
        operators.push(str[i]);
        i++; return; //小ps：若不抽象成函数，这里的 return 改成 continue 即可
    }
    while(!operators.empty() && (getPriority(str[i]) <= getPriority(operators.top())) && operands.size() >= 2){
        //注意两个操作数的顺序
        double val_2 = operands.top(); operands.pop();
        double val_1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(operatorResult(val_1, op, val_2));
    }
    operators.push(str[i]);
    i++;
}
bool Expression::isOperator(const char& ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
//中缀表达式转逆波兰表达式（后缀表达式）
//处理了一天单目减啊卧槽！！！！！！！！！！！！！！！！！！！！！！！
std::string Expression::Change_Into_ReversePolishNotation(const std::string& s){
    //思路：优先级（左括号）> 数字 > 乘除 > 加减，右括号触发弹栈
    std::string str = s, result; removeSpace(str);
    std::stack<char> operators; size_t len = str.size(); bool expectOperand = true;
    for(size_t i = 0; i < len; i++){
        //处理数字
        //数字（包括小数，负数）
        //区别于处理算术表达式的过程，这里直接将单目负号加入 result 中即可，-()的情况不用考虑（左括号触发弹栈时会包含进去） e.g.-(-(9+8))*8 ———— 9 8+- 8*-
        if(std::isdigit(str[i]) || str[i] == '.' || (i + 1 < len && expectOperand && str[i] == '-' && std::isdigit(str[i + 1]))){
            result += str[i];
            if(i + 1 < len && str[i + 1] != '.' && !std::isdigit(str[i + 1])) result += " "; //数字间加空格方便用户识别数字
        }else if(str[i] == '(') operators.push(str[i]);
        else if(str[i] == ')'){//触发弹栈
            while(!operators.empty() && operators.top() != '(') result += operators.top(), operators.pop();
            if(!operators.empty()) operators.pop();
        }else if(isOperator(str[i])){
            if(operators.empty() || (getPriority(str[i]) > operators.top())){ operators.push(str[i]); continue;} //注意要 continue，否则 error
            while(!operators.empty() && getPriority(str[i]) <= getPriority(operators.top())) result += operators.top(), operators.pop();
            operators.push(str[i]);
        }else if(str[i] == '#') result += str[i];//处理波兰表达式的时候单目负号的占位符
    }
    while(!operators.empty()) result += operators.top(), operators.pop();
    return result;
}
//中缀表达式转波兰表达式（前缀表达式）
std::string Expression::Change_Into_PolishNotation(const std::string& s){
    //思路：波兰表达式的逆向思维
    //     调换括号 ———— 将单目负号占位（在逆波兰表达式中处理使其作为数字的一部分 ———— if(str[i] == '#') result += str[i];）
    //     ———— 字符串反转 ———— 调用逆波兰表达式 ———— 字符出反转回来 ———— 恢复原单目负号占位符
    std::string str = s; size_t len = s.size();
    removeSpace(str);
    //调换括号
    for(size_t i = 0; i < len; i++){
        if(str[i] == '(') str[i] = ')';
        else if(str[i] == ')') str[i] = '(';
    }
    //单目负号占位
    for(size_t i = 0; i < len; i++) if(str[i] == '-' && (i == 0 || (!std::isdigit(str[i - 1]) && str[i - 1] != '('))) str[i] = '#';
    //字符串反转
    std::reverse(str.begin(), str.end());
    //调用逆波兰表达式
    str = Change_Into_ReversePolishNotation(str);
    //字符串反转回来
    std::reverse(str.begin(), str.end());
    //恢复原单目负号占位符
    for(char& ch : str) if(ch == '#') ch = '-';
    return str;
}
