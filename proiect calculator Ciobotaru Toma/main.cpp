#include "CalculatorUI.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    CalculatorUI calculator;

    if (argc > 1) {
        string ecuatie = argv[1];
        calculator.proceseazaEcuatie(ecuatie);
    } else {
        calculator.executa();
    }

    return 0;
}