#ifndef MEDIC_H
#define MEDIC_H

#include "Persoana.h"
#include <map>

class FisaMedicala;

class Medic : public Persoana {
    string specializare;
    float nota;
    string grad;
    map<int, string> programari;

public:
    Medic();
    Medic(string, string, string, string, float, string);
    void afisare() override;
    string getGrad() const { return this->grad; }
    string getSpecializare() const { return this->specializare; }
    float getNota() const { return this->nota; }
    map<int, string> getProgramari() const { return this->programari; }
    void setProgramari(const map<int, string>& prog) { programari = prog; }
    void afisareStilizata() const;
    bool esteDisponibil(int ora);
    void adaugaProgramare(const string& emailPacient, int ora);
    void stergeProgramare(int ora);
    void vizualizeazaProgramari();
    friend class FisaMedicala;
};

#endif // MEDIC_H
