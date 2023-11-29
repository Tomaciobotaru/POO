#include "ExpressionParser.h"
#include <iostream>
#include <cstring>
#include <cctype>

ExpressionParser::ExpressionParser() : expresie(new char[maxLungime]()) {}

ExpressionParser::ExpressionParser(const string& str) : expresie(new char[maxLungime]()) {
    strncpy(expresie, str.c_str(), maxLungime);
}

ExpressionParser::~ExpressionParser() {
    delete[] expresie;
}

ExpressionParser::ExpressionParser(const ExpressionParser& other) : expresie(new char[maxLungime]()) {
    strncpy(expresie, other.expresie, maxLungime);
}

ExpressionParser& ExpressionParser::operator=(const ExpressionParser& other) {
    if (this != &other) {
        delete[] expresie;
        expresie = new char[maxLungime]();
        strncpy(expresie, other.expresie, maxLungime);
    }
    return *this;
}
const char& ExpressionParser::operator[](int index) const {
    if (index >= 0 && index < strlen(expresie)) {
        return expresie[index];
    }
    throw std::out_of_range("Index invalid");
}
ExpressionParser::operator string() const {
    return string(expresie);
}
bool ExpressionParser::esteValid(char caracter) {
    return isdigit(caracter) || esteOperator(caracter) || caracter == '(' || caracter == ')' || caracter == '[' || caracter == ']' || caracter == '.' || caracter == '^' || caracter == '#';
}

bool ExpressionParser::parantezeEchilibrate(const string& expresie) {
    char stack[maxLungime];
    int top = -1;
    for (char c : expresie) {
        if (c == '(' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == ']') {
            if (top == -1 || (c == ')' && stack[top] != '(') || (c == ']' && stack[top] != '[')) return false;
            top--;
        }
    }
    return top == -1;
}

int ExpressionParser::prioritate(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' || op == '#') return 3;
    return 0;
}

bool ExpressionParser::esteOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#';
}

string ExpressionParser::convertToPostfix() {
    char stack[maxLungime];
    int top = -1;
    string postfix;
    for (int i = 0; i < strlen(expresie); ++i) {
        char c = expresie[i];
        if (esteCaracter(c) || (c == '.' && i > 0 && isdigit(expresie[i-1]) && isdigit(expresie[i+1]))) {
            postfix += c;
            
            if (i + 1 == strlen(expresie) || (!esteCaracter(expresie[i + 1]) && expresie[i + 1] != '.')) {
                postfix += ' '; 
            }
        } else if (c == '(' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == ']') {
            char coresp = (c == ')') ? '(' : '[';
            while (top != -1 && stack[top] != coresp) {
                postfix += stack[top--];
                postfix += ' ';
            }
            top--; 
        } else if (esteOperator(c)) {
            while (top != -1 && prioritate(stack[top]) >= prioritate(c)) {
                postfix += stack[top--];
                postfix += ' ';
            }
            stack[++top] = c; 
        }
    }
    while (top != -1) {
        postfix += stack[top--];
        postfix += ' ';
    }
    return postfix;
}


bool ExpressionParser::esteCaracter(char c) {
    return isdigit(c) || isalpha(c) || c == '.';
}
string ExpressionParser::getExpresie() const {
    return string(expresie);
}
void ExpressionParser::setExpresie(const string& nouaExpresie) {
    if (nouaExpresie.length() >= maxLungime) {
        cerr << "Expresia este prea lungă. Maxim permis: " << maxLungime - 1 << " caractere." << endl;
       
        return;
    }
    strncpy(expresie, nouaExpresie.c_str(), maxLungime);
    expresie[maxLungime - 1] = '\0'; 
}





ostream& operator<<(ostream& os, const ExpressionParser& parser) {
    os << parser.expresie;
    return os;
}
istream& operator>>(istream& in, ExpressionParser& parser) {
    cout << "Introduceti expresia: ";
    string expresie;
    getline(in, expresie);
    parser.setExpresie(expresie);
    return in;
}
