#include "Medic.h"
#include "FisaMedicala.h"
#include "FileIO.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

Medic::Medic() : Persoana() {
    this->specializare = "Necunoscut";
    this->nota = 0.0;
    this->grad = "Necunoscut";
}

Medic::Medic(string nume, string prenume, string email, string specializare, float nota, string grad)
    : Persoana(nume, prenume, email) {
    this->specializare = specializare;
    this->nota = nota;
    this->grad = grad;
}

void Medic::afisare() {
    Persoana::afisare();
    cout << "Specializare: " << this->specializare << endl;
    cout << "Nota: " << this->nota << endl;
    cout << "Grad: " << this->grad << endl;
}

void Medic::afisareStilizata() const {
    int maxLength = 0;
    maxLength = max(maxLength, static_cast<int>(string("Nume: " + getNume()).length()));
    maxLength = max(maxLength, static_cast<int>(string("Prenume: " + getPrenume()).length()));
    maxLength = max(maxLength, static_cast<int>(string("Email: " + getEmail()).length()));
    maxLength = max(maxLength, static_cast<int>(string("Specializare: " + getSpecializare()).length()));
    maxLength = max(maxLength, static_cast<int>(string("Nota: " + to_string(nota)).length()));
    maxLength = max(maxLength, static_cast<int>(string("Grad: " + getGrad()).length()));

    int totalWidth = maxLength + 4;
    string border(totalWidth, '-');

    cout << "+" << border << "+" << endl;
    cout << "| Profil Medic" << setw(totalWidth - 12) << right << " |" << endl;
    cout << "+" << border << "+" << endl;
    cout << "| Nume: " << setw(totalWidth - 7) << left << nume << "|" << endl;
    cout << "| Prenume: " << setw(totalWidth - 10) << left << prenume << "|" << endl;
    cout << "| Email: " << setw(totalWidth - 8) << left << email << "|" << endl;
    cout << "| Specializare: " << setw(totalWidth - 15) << left << specializare << "|" << endl;
    cout << "| Nota: " << setw(totalWidth - 7) << left << nota << "|" << endl;
    cout << "| Grad: " << setw(totalWidth - 7) << left << grad << "|" << endl;
    cout << "+" << border << "+" << endl;
}

bool Medic::esteDisponibil(int ora) {
    return programari.find(ora) == programari.end();
}

void Medic::adaugaProgramare(const string& emailPacient, int ora) {
    if (esteDisponibil(ora)) {
        programari[ora] = emailPacient;
    } else {
        cout << "Ora nu este disponibila!" << endl;
    }
}

void Medic::stergeProgramare(int ora) {
    programari.erase(ora);
}

void Medic::vizualizeazaProgramari() {
    for (const auto& programare : programari) {
        cout << "Ora: " << programare.first << " - Pacient: " << programare.second << endl;
    }
}


