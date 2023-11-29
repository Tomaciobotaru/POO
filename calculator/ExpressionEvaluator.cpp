#include "ExpressionEvaluator.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <limits>
using namespace std;

ExpressionEvaluator::ExpressionEvaluator() : top(-1), expresiePostfixata("") {}

ExpressionEvaluator::ExpressionEvaluator(const string& expresiePostfixata) : top(-1), expresiePostfixata(expresiePostfixata) {}

ExpressionEvaluator::ExpressionEvaluator(const ExpressionEvaluator& other)
    : top(other.top), expresiePostfixata(other.expresiePostfixata) {
    
    for (int i = 0; i <= top; ++i) {
        stack[i] = other.stack[i];
    }
}
bool ExpressionEvaluator::operator!() const {
    return expresiePostfixata.empty();
}
ExpressionEvaluator& ExpressionEvaluator::operator++() {
    double rezultat = eval();
    rezultat++; 

    return *this;
}


ExpressionEvaluator ExpressionEvaluator::operator++(int) {
    ExpressionEvaluator copieTemporara = *this; 
    ++(*this); 

    return copieTemporara; 
}


ExpressionEvaluator& ExpressionEvaluator::operator=(const ExpressionEvaluator& other) {
    if (this != &other) {
        
        top = other.top;
        expresiePostfixata = other.expresiePostfixata;

        
        for (int i = 0; i <= top; ++i) {
            stack[i] = other.stack[i];
        }
    }
    return *this;
}

ExpressionEvaluator::~ExpressionEvaluator() = default;

double ExpressionEvaluator::aplicaOperator(double a, double b, char op) {
    switch (op) {
        case '+': 
            return a + b;
        case '-': 
            return a - b;
        case '*': 
            return a * b;
        case '/': 
            if (b == 0) {
                cerr << "Impartire la zero!" << endl;
                std::numeric_limits<double>::quiet_NaN(); 
            }
            return a / b;
        case '^': 
            return pow(a, b); 
        case '#': 
            return calculeazaRadical(a, b); 
        default: 
            cerr << "Operator necunoscut: " << op << endl;
            std::numeric_limits<double>::quiet_NaN();
    }
}

double ExpressionEvaluator::calculeazaRadical(double x, double y) {
    if (y < 0 || (x == 0 && y == 0)) {
        cerr << "Parametri invalizi pentru radical." << endl;
        std::numeric_limits<double>::quiet_NaN();
    }
    return pow(y, 1.0 / x);
}


const string& ExpressionEvaluator::getExpresiePostfixata() const {
    return expresiePostfixata;
}


void ExpressionEvaluator::setExpresiePostfixata(const string& nouaExpresie) {
    
    if (nouaExpresie.length() > maxDimensiune) {
        throw std::runtime_error("Expresia este prea lungă.");
    }

    
    for (char c : nouaExpresie) {
        if (!isdigit(c) && !isspace(c) && c != '.' && !ExpressionParser::esteOperator(c)) {
            throw std::runtime_error("Expresia conține caractere nepermise.");
        }
    }

    
    expresiePostfixata = nouaExpresie;
}


double ExpressionEvaluator::eval()  {
    if (expresiePostfixata.empty()) return 0;

    char* postfix = new char[expresiePostfixata.length() + 1];
    strcpy(postfix, expresiePostfixata.c_str());

    char* token = strtok(postfix, " ");
    while (token != nullptr) {
        std::istringstream iss(token);
        double num;
        if (iss >> num) { 
            stack[++top] = num; 
        } else if (strlen(token) == 1 && ExpressionParser::esteOperator(token[0])) {
            if (top < 1) {
                delete[] postfix;
                throw std::runtime_error("Expresie invalida: prea putini operanzi pentru operator");
            }
            double b = stack[top--];
            double a = stack[top--];
            stack[++top] = aplicaOperator(a, b, token[0]);
        } else {
            delete[] postfix;
            throw std::runtime_error("Expresie invalida: token necunoscut sau incorect");
        }
        token = strtok(nullptr, " ");
    }

    if (top != 0) {
        delete[] postfix;
        throw std::runtime_error("Expresie invalida: dezechilibru între operatori si operanzi");
    }

    double result = stack[top];
    delete[] postfix;
    return result;
}



ostream& operator<<(ostream& os, const ExpressionEvaluator& evaluator) {
    os << evaluator.expresiePostfixata;
    return os;
}
istream& operator>>(istream& in, ExpressionEvaluator& evaluator) {
    cout << "Introduceti expresia postfixata: ";
    string expresiePostfixata;
    getline(in, expresiePostfixata);
    evaluator.setExpresiePostfixata(expresiePostfixata);
    return in;
}
