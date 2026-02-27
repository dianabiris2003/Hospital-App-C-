#ifndef PERSOANA_H
#define PERSOANA_H

#include <iostream>
#include <string>
using namespace std;

class Persoana {
protected:
    string nume;
    string prenume;
    string email;

public:
    Persoana();
    Persoana(string, string, string);
    virtual void afisare();
    string getNume() const { return nume; }
    string getPrenume() const { return prenume; }
    string getEmail() const { return email; }
    friend class FisaMedicala;
};



#endif //PERSOANA_H
