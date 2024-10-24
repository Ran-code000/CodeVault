QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnifiedCalculator
TEMPLATE = app

SOURCES += main.cpp \
           calculator.cpp \
           polynomial.cpp \
           expression.cpp

HEADERS += calculator.h \
           polynomial.h \
           expression.h

FORMS +=
