#include "calculator.h"
#include "polynomial.h"
#include "expression.h"

#include <QVBoxLayout> //垂直布局管理器，按垂直顺序排列组件
#include <QHBoxLayout> //水平布局管理器，按水平方向排列组件
#include <QMessageBox> //用于显示错误或警告对话框（弹出的 error 对话框）

Calculator::Calculator(QWidget* parent) : QWidget(parent){
    //初始化私有成员变量
    //单行文本输入框
    inputFirstPolynomial = new QLineEdit(this);
    inputSecondPolynomial = new QLineEdit(this);
    inputX = new QLineEdit(this);
    inputExpression = new QLineEdit(this);
    //静态标签（设置解释显示信息的文本和解释信息）
    PolynomialsResult = new QLabel("Polynomials result: ", this);
    ExpressionResult = new QLabel("Expression result: ", this);
    ReversePolishNotationResult = new QLabel("ReversePolishNotation result: ", this);
    PolishNotationResult = new QLabel("PolishNotation result: ", this);
    //添加按钮（设置按钮名称 ———— 显示在窗口上提示用户）
    QPushButton* addPolynomialButton = new QPushButton("addPolynomial");
    QPushButton* substractPolynomialButton = new QPushButton("substractPolynomial");
    QPushButton* multiplyPolynomialButton = new QPushButton("multiplyPolynomial");
    QPushButton* derivativePolynomialButton = new QPushButton("derivativePolynomial");
    QPushButton* evaluatePolynomialButton = new QPushButton("evaluatePolynomial");
    QPushButton* evaluateExpressionButton = new QPushButton("evaluteExpression");
    QPushButton* ReversePolishNotationButton = new QPushButton("reversePolishNotation");
    QPushButton* PolishNotationButton = new QPushButton("PolishNotation");

    //Vlayout 作为主垂直布局，依次添加水平布局（p->addLayout(*QHBoxLayout)）、按钮（p->addWidget(*QPushButton）、结果显示标签（p->addWidget(*QLabel)）和文本输入框（p->addWidget(*QLineEdit)）
    QVBoxLayout* Vlayout = new QVBoxLayout(this);
    QHBoxLayout* pH_0 = new QHBoxLayout(), *pH_1 = new QHBoxLayout(), *pH_2 = new QHBoxLayout(), *pH_3 = new QHBoxLayout(), *pH_4 = new QHBoxLayout(), *pH_5 = new QHBoxLayout();;
    //布局中添加控件
    pH_0->addWidget(new QLabel("FirstPolynomial: "));
    pH_0->addWidget(inputFirstPolynomial);
    pH_0->addWidget(new QLabel("SecondPolynomial: "));
    pH_0->addWidget(inputSecondPolynomial);
    pH_0->addWidget(new QLabel("The value of x"));
    pH_0->addWidget(inputX);
    pH_1->addWidget(addPolynomialButton);
    pH_1->addWidget(substractPolynomialButton);
    pH_2->addWidget(multiplyPolynomialButton);
    pH_2->addWidget(derivativePolynomialButton);
    pH_3->addWidget(evaluatePolynomialButton);
    pH_4->addWidget(ReversePolishNotationButton);
    pH_4->addWidget(PolishNotationButton);
    Vlayout->addLayout(pH_0);
    Vlayout->addLayout(pH_1);
    Vlayout->addLayout(pH_2);
    Vlayout->addLayout(pH_3);
    Vlayout->addWidget(PolynomialsResult);
    pH_5->addWidget(new QLabel("Input an expression: "));
    pH_5->addWidget(inputExpression);
    Vlayout->addLayout(pH_5);
    Vlayout->addLayout(pH_4);
    Vlayout->addWidget(evaluateExpressionButton);
    Vlayout->addWidget(ExpressionResult);
    Vlayout->addWidget(ReversePolishNotationResult);
    Vlayout->addWidget(PolishNotationResult);
    //connect()：Qt 的信号和槽机制，连接按钮的 clicked 信号与相应的槽函数（如 addPolynomials()）。当用户点击按钮时，对应的槽函数将被执行
    connect(addPolynomialButton, &QPushButton::clicked, this, &Calculator::addPolynomials);
    connect(substractPolynomialButton, &QPushButton::clicked, this, &Calculator::subtractPolynomials);
    connect(multiplyPolynomialButton, &QPushButton::clicked, this, &Calculator::multiplyPolynomials);
    connect(derivativePolynomialButton, &QPushButton::clicked, this, &Calculator::derivativePolynomials);
    connect(evaluatePolynomialButton, &QPushButton::clicked, this, &Calculator::evaluatePolynomials);
    connect(evaluateExpressionButton, &QPushButton::clicked, this, &Calculator::evaluateExpression);
    connect(ReversePolishNotationButton, &QPushButton::clicked, this, &Calculator::evaluateReversePolishNotation);
    connect(PolishNotationButton, &QPushButton::clicked, this, &Calculator::evaluatePolishNotation);

}
//定义槽函数
//try-catch：捕获异常并在错误时通过 QMessageBox(父窗口，警告框 title，错误信息) 显示警告
//主要思路：text()方法获取文本信息（QString 类型）———— toStdString() 获取 c++ 标准类型字符串 ———— 处理字符串（根据不同类内部实现的功能（调用成员函数）实现）
//       ———— 用 QString::fromStdString 方法将字符出转化为 QString 类型；用 QString::number 方法将数字出转化为 QString 类型
void Calculator::addPolynomials() {
    Polynomial poly1, poly2;
    try {
        poly1.from_String_to_Terms(inputFirstPolynomial->text().toStdString());
        poly2.from_String_to_Terms(inputSecondPolynomial->text().toStdString());
        Polynomial result = poly1.add(poly2);
        PolynomialsResult->setText("Polynomial Result: " + QString::fromStdString(result.from_Terms_to_String()));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::subtractPolynomials() {
    Polynomial poly1, poly2;
    try {
        poly1.from_String_to_Terms(inputFirstPolynomial->text().toStdString());
        poly2.from_String_to_Terms(inputSecondPolynomial->text().toStdString());
        Polynomial result = poly1.subtract(poly2);
        PolynomialsResult->setText("Polynomial Result: " + QString::fromStdString(result.from_Terms_to_String()));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::multiplyPolynomials() {
    Polynomial poly1, poly2;
    try{
        poly1.from_String_to_Terms(inputFirstPolynomial->text().toStdString());
        poly2.from_String_to_Terms(inputSecondPolynomial->text().toStdString());
        Polynomial result = poly1.multiply(poly2);
        PolynomialsResult->setText("Polynomial Result: " + QString::fromStdString(result.from_Terms_to_String()));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::derivativePolynomials(){
    Polynomial poly;
    try{
        poly.from_String_to_Terms(inputFirstPolynomial->text().toStdString());
        Polynomial result = poly.derivative();
        PolynomialsResult->setText("Polynomial Result: " + QString::fromStdString(result.from_Terms_to_String()));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::evaluatePolynomials(){
    Polynomial poly;
    try{
        poly.from_String_to_Terms(inputFirstPolynomial->text().toStdString());
        double result = poly.evaluate(inputX->text().toDouble());
        PolynomialsResult->setText("Polynomial Result: " + QString::number(result));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::evaluateExpression() {
    Expression expr;
    try{
        double result = expr.evaluate(inputExpression->text().toStdString());
        ExpressionResult->setText("Expression Result: " + QString::number(result));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}

void Calculator::evaluatePolishNotation(){
    Expression expr;
    try{
        std::string result = expr.Change_Into_PolishNotation(inputExpression->text().toStdString());
        ReversePolishNotationResult->setText("PolishNotation Result: " + QString::fromStdString(result));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}
void Calculator::evaluateReversePolishNotation(){
    Expression expr;
    try{
        std::string result = expr.Change_Into_ReversePolishNotation(inputExpression->text().toStdString());
        PolishNotationResult->setText("ReversePolishNotation Result: " + QString::fromStdString(result));
    }catch(const std::exception& e){
        QMessageBox::warning(this, "Error", e.what());
    }
}
