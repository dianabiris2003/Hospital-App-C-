#include "FisaMedicala.h"
#include <iostream>

void FisaMedicala::afisare() const {
    cout << "Email pacient: " << emailPacient << endl;
    cout << "Diagnostice si Medici:" << endl;
    for (const auto& entry : diagnostice) {
        cout << "Diagnostic: " << entry.first << " - Medic: " << entry.second->getNume() << " " << entry.second->getPrenume() << endl;
    }
}

