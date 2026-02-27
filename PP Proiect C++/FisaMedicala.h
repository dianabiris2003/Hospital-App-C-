#ifndef FISAMEDICALA_H
#define FISAMEDICALA_H

#include <vector>
#include <string>
#include <memory>
#include "Pacient.h"
#include "Medic.h"
using namespace std;

class Pacient;
class Medic;

class FisaMedicala {
    string emailPacient;
    map<string, unique_ptr<Medic>> diagnostice;


public:
    FisaMedicala() {}
    FisaMedicala(const string& email, map<string, unique_ptr<Medic>>& diag)
        : emailPacient(email), diagnostice(move(diag)) {}

    void afisare() const;
    void setDiagnostic(map<string, unique_ptr<Medic>>& diag) { diagnostice = move(diag); };
    void adaugaDiagnostic(const string& diag, unique_ptr<Medic> medic) {
        diagnostice[diag] = move(medic);
    }
    const map<string, unique_ptr<Medic>>& getDiagnostice() const {
        return diagnostice;
    }
    const string& getEmailPacient() const {
        return emailPacient;
    }
};


#endif // FISAMEDICALA_H
