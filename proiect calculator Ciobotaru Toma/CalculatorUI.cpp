#include "CalculatorUI.h"

const string CalculatorUI::mesajBunVenit = "Bun venit la Calculatorul Stiintific!";
const string CalculatorUI::mesajInstructiuni = "Introduceti expresia si apasati Enter. Scrie 'exit' pentru a iesi.";
const string CalculatorUI::mesajIesire = "Iesire din calculator.";



CalculatorUI::CalculatorUI() : CalculatorBaza(), ultimulRezultat(0.0) {}
    

void CalculatorUI::afiseazaMesajBunVenit() const {
    cout << "Bun venit la Calculatorul Stiintific!" << endl;
}
void CalculatorUI::salveazaRezultat(const string& numeFisier) {
    ofstream fisierOut(numeFisier, ios::binary);
    if (fisierOut.is_open()) {
        fisierOut.write(reinterpret_cast<const char*>(&ultimulRezultat), sizeof(ultimulRezultat));
    }
    fisierOut.close();
}
void CalculatorUI::incarcaRezultat(const string& numeFisier) {
    ifstream fisierIn(numeFisier, ios::binary);
    if (fisierIn.is_open()) {
        fisierIn.read(reinterpret_cast<char*>(&ultimulRezultat), sizeof(ultimulRezultat));
    }
    fisierIn.close();
}



bool CalculatorUI::operator<(const CalculatorUI& altUI) const {
    return this->expresieCurenta.length() < altUI.expresieCurenta.length();
}
double CalculatorUI::operator-(const CalculatorUI& altUI) const {
    int lungimeAceasta = this->expresieCurenta.length();
    int lungimeAlta = altUI.expresieCurenta.length();
    return static_cast<double>(lungimeAceasta - lungimeAlta);
}

void CalculatorUI::afiseazaInstructiuni() const {
    cout << "Introduceti expresia si apasati Enter. Scrie 'exit' pentru a iesi." << endl;
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
            if (rezultat==0)
            {
                rezultat=0;
            }

           
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(10) << rezultat;
            string rezultatFormatat = oss.str();

            
            rezultatFormatat.erase(rezultatFormatat.find_last_not_of('0') + 1, std::string::npos);
            if (rezultatFormatat.back() == '.') {
                rezultatFormatat.pop_back();  
            }

            cout << "Rezultat: " << rezultatFormatat << endl;
        } catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
        }
    }
}
void CalculatorUI::proceseazaEcuatie(const string& ecuatie) {
    try {
        parser = ExpressionParser(ecuatie);
        expresieCurenta = parser.convertToPostfix();
        evaluator = ExpressionEvaluator(expresieCurenta);
        double rezultat = evaluator.eval();
        cout << "Rezultat: " << rezultat << endl;
    } catch (const exception& e) {
        cout << "Eroare: " << e.what() << endl;
    }
}
void CalculatorUI::afiseazaMeniu() {
    cout << "\nMeniu:" << endl;
    cout << "1. Introducere ecuatie" << endl;
    cout << "2. Citeste ecuatii din fisier" << endl;
    cout << "3. Salveaza ultimul rezultat" << endl;
    cout << "4. Incarca un rezultat salvat" << endl;
    cout << "5. Iesire" << endl;
    cout << "Alegeti o optiune: ";
}
void CalculatorUI::executaAlegereaMeniului(int alegere) {
    switch (alegere) {
    
            
            case 1:
            
            {
                string ecuatie;
                while (true) {
                    cout << "Introduceti ecuatia (sau 'exit' pentru a reveni la meniu): ";
                    getline(cin, ecuatie);

                    if (ecuatie == "exit") {
                        break;  
                    }

                    proceseazaEcuatie(ecuatie);
                }
            }
            break;
        case 2:
            
            {
                string numeFisier;
                cout << "Introduceti numele fisierului: ";
                getline(cin, numeFisier);
                citesteSiProceseazaEcuatiiDinFisier(numeFisier);
                break;
            }
        
        case 3:
            
            {
                string numeFisier;
                cout << "Introduceti numele fisierului pentru salvare: ";
                getline(cin, numeFisier);
                salveazaRezultat(numeFisier);
            }
            break;
        case 4:
            
            {
                string numeFisier;
                cout << "Introduceti numele fisierului pentru incarcare: ";
                getline(cin, numeFisier);
                incarcaRezultat(numeFisier);
            }
            break;
        case 5:
            
            cout << "Iesire din program." << endl;
            exit(0); 
            break;
        default:
            cout << "Optiune invalida!" << endl;
    }
}

void CalculatorUI::executa() {
    while (true) {
        afiseazaMeniu();
        int alegere;
        if (!(cin >> alegere)) {
            cin.clear(); // Resetează starea stream-ului în caz de eroare
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoră restul liniei
            cout << "Input invalid. Introduceti un numar." << endl;
            continue;
        }
        cin.ignore(); // Ignoră newline-ul rămas în buffer

        if (alegere == 5) {
            break;
        }

        executaAlegereaMeniului(alegere);
    }
}
void CalculatorUI::citesteSiProceseazaEcuatiiDinFisier(const string& numeFisier) {
    ifstream fisier(numeFisier);
    string ecuatie;

    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fisierul: " << numeFisier << endl;
        return; 
    }

    while (getline(fisier, ecuatie)) {
        if (fisier.fail()) {
            cerr << "Eroare la citirea din fisier." << endl;
            break; 
        }

        if (!ecuatie.empty()) {
            proceseazaEcuatie(ecuatie);
        }
    }

    fisier.close();
}

      