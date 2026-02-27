#ifndef PACIENT_H
#define PACIENT_H

#include "Persoana.h"
#include "FisaMedicala.h"
#include "Medic.h"
#include <map>
#include <vector>

class Medic;
class FisaMedicala;

class Pacient : public Persoana {
    int varsta;
    bool asigurat;
    FisaMedicala* fisa;
    map<int, string> programari;

public:
    Pacient();
    Pacient(string, string, string, int, bool);
    void afisare() override;
    void afisareFisa() const;
    void setFisa(FisaMedicala*);
    FisaMedicala* getFisa() const { return this->fisa; }
    int getVarsta() const { return this->varsta; }
    bool getAsigurat() const { return this->asigurat; }
    map<int, string> getProgramari() const { return this->programari; }
    void afisareStilizata() const;
    void setProgramari(const map<int, string>& prog) { programari = prog; }
    void adaugaProgramare(const string &emailMedic, int ora);
    void stergeProgramare(int ora);
    void vizualizeazaProgramari();
    friend class FisaMedicala;
};

#endif // PACIENT_H
