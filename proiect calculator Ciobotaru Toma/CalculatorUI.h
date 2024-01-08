#ifndef CALCULATORUI_H
#define CALCULATORUI_H
#include "CalculatorBaza.h"
#include "ExpressionParser.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

class CalculatorUI: public CalculatorBaza{
private:
    ExpressionParser parser;
    double ultimulRezultat;
    ExpressionEvaluator evaluator;
    string expresieCurenta;
    static const string mesajBunVenit;
    static const string mesajInstructiuni;
    static const string mesajIesire;

public:
    CalculatorUI();
    CalculatorUI(const CalculatorUI& other) = default;
    void ruleaza();
    void proceseazaEcuatie(const string& ecuatie);
    void citesteSiProceseazaEcuatiiDinFisier(const string& numeFisier);
    virtual void afiseazaMesajBunVenit() const override;
    virtual void afiseazaInstructiuni() const override;
    string getExpresieCurenta() const;
    void setExpresieCurenta(const string& nouaExpresie);
    friend ostream& operator <<(ostream& os,const CalculatorUI);
    friend istream& operator>>(istream& in, CalculatorUI& ui);
    bool operator<(const CalculatorUI& altUI) const;
   double operator-(const CalculatorUI& altUI) const;
   void salveazaRezultat(const string& numeFisier);
    void incarcaRezultat(const string& numeFisier);
    void afiseazaMeniu();
    void executaAlegereaMeniului(int alegere);
    void executa() override;
};

#endif // CALCULATORUI_H
