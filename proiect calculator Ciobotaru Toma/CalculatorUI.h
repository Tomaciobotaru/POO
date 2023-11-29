#ifndef CALCULATORUI_H
#define CALCULATORUI_H

#include "ExpressionParser.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <string>

using namespace std;

class CalculatorUI {
private:
    ExpressionParser parser;
    ExpressionEvaluator evaluator;
    string expresieCurenta;
    static const string mesajBunVenit;
    static const string mesajInstructiuni;
    static const string mesajIesire;

public:
    CalculatorUI();
    CalculatorUI(const CalculatorUI& other) = default;
    void ruleaza();
    void afiseazaMesajBunVenit() const;
    static void afiseazaInstructiuni();
    string getExpresieCurenta() const;
    void setExpresieCurenta(const string& nouaExpresie);
    friend ostream& operator <<(ostream& os,const CalculatorUI);
    friend istream& operator>>(istream& in, CalculatorUI& ui);
    bool operator<(const CalculatorUI& altUI) const;
   double operator-(const CalculatorUI& altUI) const;
    
};

#endif // CALCULATORUI_H
