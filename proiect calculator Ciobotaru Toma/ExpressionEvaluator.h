#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include "ExpressionParser.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class ExpressionEvaluator {
private:
    static const int maxDimensiune = 1000; 
    double stack[maxDimensiune]; 
    int top; 
    string expresiePostfixata;

    double aplicaOperator(double a, double b, char op);
    double calculeazaRadical(double x, double y);

public:
    ExpressionEvaluator();
    ExpressionEvaluator(const string& expresiePostfixata);
    ExpressionEvaluator(const ExpressionEvaluator& other);
    ExpressionEvaluator& operator=(const ExpressionEvaluator& other);
    ~ExpressionEvaluator();
    const string& getExpresiePostfixata() const;
   void setExpresiePostfixata(const string& nouaExpresie);
    double eval() ;
    bool operator!() const;
    ExpressionEvaluator& operator++();    
    ExpressionEvaluator operator++(int);
    friend ostream& operator<<(ostream& os, const ExpressionEvaluator& evaluator);
    friend istream& operator>>(istream& in, ExpressionEvaluator& evaluator);
};

#endif // EXPRESSIONEVALUATOR_H
