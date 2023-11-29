#include "CalculatorUI.h"

const string CalculatorUI::mesajBunVenit = "Bun venit la Calculatorul Stiintific!";
const string CalculatorUI::mesajInstructiuni = "Introduceti expresia si apasati Enter. Scrie 'exit' pentru a iesi.";
const string CalculatorUI::mesajIesire = "Iesire din calculator.";

CalculatorUI::CalculatorUI() {
    
}

void CalculatorUI::afiseazaMesajBunVenit() const {
    cout << mesajBunVenit << endl;
}


bool CalculatorUI::operator<(const CalculatorUI& altUI) const {
    return this->expresieCurenta.length() < altUI.expresieCurenta.length();
}
double CalculatorUI::operator-(const CalculatorUI& altUI) const {
    int lungimeAceasta = this->expresieCurenta.length();
    int lungimeAlta = altUI.expresieCurenta.length();
    return static_cast<double>(lungimeAceasta - lungimeAlta);
}

void CalculatorUI::afiseazaInstructiuni() {
    cout << mesajInstructiuni << endl;
}
string CalculatorUI::getExpresieCurenta() const {
    return expresieCurenta;
}
void CalculatorUI::setExpresieCurenta(const string& nouaExpresie) {
    
    if (nouaExpresie.length() > 1000) { 
        cout << "Expresia este prea lungă. Limita maximă este de 1000 de caractere." << endl;
        return;
    }

    
    if (nouaExpresie.find_first_not_of("0123456789+-*/^()[]#., ") != string::npos) {
        cout << "Expresia conține caractere nepermise." << endl;
        return;
    }

    
    expresieCurenta = nouaExpresie;
}
ostream& operator<<(ostream& os,const CalculatorUI& ui)
{ os << "Expresie Curenta: " << ui.getExpresieCurenta();
   return os;
}
istream& operator>>(istream& in, CalculatorUI& ui) {
    cout << "Introduceti expresia: ";
    string expresie;
    getline(in, expresie);
    ui.setExpresieCurenta(expresie);
    return in;
}


void CalculatorUI::ruleaza() {
    afiseazaMesajBunVenit();
    afiseazaInstructiuni();
    
    string input;
    while (true) {
        cout << "\nExpresie: ";
        getline(cin, input);

        if (input == "exit") {
            cout << mesajIesire << endl;
            break;
        }

        try {
            parser = ExpressionParser(input); 
            expresieCurenta = parser.convertToPostfix(); 
            evaluator = ExpressionEvaluator(expresieCurenta); 
            double rezultat = evaluator.eval(); 
            cout << "Rezultat: " << rezultat << endl;
        } catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
        }
    }
}
