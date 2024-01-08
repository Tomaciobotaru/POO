#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class ExpressionParser {
    friend class ExpressionEvaluator;
private:
    char* expresie; 
    static const int maxLungime = 1000; 

    static bool esteValid(char caracter);
    bool parantezeEchilibrate(const string& expresie);
    int prioritate(char op);
    static bool esteOperator(char c);

public:
    ExpressionParser();
    ExpressionParser(const string& str);
    ExpressionParser(const ExpressionParser& other);
    ExpressionParser& operator=(const ExpressionParser& other);
    ~ExpressionParser();
    string getExpresie() const;
    void setExpresie(const string& nouaExpresie);
    string convertToPostfix();
    static bool esteCaracter(char c); // Metodă statică
    friend ostream& operator<<(ostream& os, const ExpressionParser& parser);
    friend istream& operator>>(istream& in, ExpressionParser& parser);
    const char& operator[](int index) const;
    explicit operator string() const;
    static bool esteNumarValid(const string& numar);
};

#endif // EXPRESSIONPARSER_H
