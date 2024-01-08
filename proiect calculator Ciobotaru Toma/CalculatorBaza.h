#ifndef CALCULATORBAZA_H
#define CALCULATORBAZA_H

#include <iostream>
#include <string>
using namespace std;


class CalculatorBaza {
public:
    virtual void executa() = 0;  
    virtual void afiseazaMesajBunVenit() const {
        cout<< "Bun venit la Calculator!" << endl;
    }

    virtual void afiseazaInstructiuni() const {
        cout<< "Introduceti comenzi." << endl;
    }

};

#endif // CALCULATORBAZA_H