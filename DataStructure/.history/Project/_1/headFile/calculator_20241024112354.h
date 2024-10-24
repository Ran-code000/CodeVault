#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);

private slots:
    void addPolynomials();
    void subtractPolynomials();
    void multiplyPolynomials();
    void derivativePolynomials();
    void evaluatePolynomials();
    void evaluateExpression();
    void evaluatePolishNotation();
    void evaluateReversePolishNotation();
private:
    QLineEdit* inputFirstPolynomial;
    QLineEdit* inputSecondPolynomial;
    QLineEdit* inputX;
    QLineEdit* inputExpression;
    QLabel* PolynomialsResult;
    QLabel* ReversePolishNotationResult;
    QLabel* PolishNotationResult;
    QLabel* ExpressionResult;
};

#endifr