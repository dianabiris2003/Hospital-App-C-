#include "Pacient.h"
#include "FileIO.h"
#include <sstream>
#include <iomanip>

Pacient::Pacient() : Persoana() {
    this->varsta=0;
    this->asigurat=false;
}

Pacient::Pacient(string nume, string prenume, string email, int varsta, bool asigurat)
    : Persoana(nume, prenume, email) {
    this->varsta=varsta;
    this->asigurat=asigurat;
}

void Pacient::afisare() {
    Persoana::afisare();
    cout<<"Varsta: "<<this->varsta<<endl;
    cout<<"Asigurat: "<<(this->asigurat ? "Da":"Nu")<<endl;
}

void Pacient::afisareFisa() const {
    fisa->afisare();
}

void Pacient::setFisa(FisaMedicala* f) {
    delete fisa;
    this->fisa=f;
}

void Pacient::afisareStilizata() const {
    int maxLength=0;
    maxLength=max(maxLength, static_cast<int>(string("Nume: " + nume).length()));
    maxLength=max(maxLength, static_cast<int>(string("Prenume: " + prenume).length()));
    maxLength=max(maxLength, static_cast<int>(string("Email: " + email).length()));
    maxLength=max(maxLength, static_cast<int>(string("Varsta la ultimul control: " + to_string(varsta)).length()));
    maxLength=max(maxLength, static_cast<int>(string("Asigurat: " + string(asigurat ? "Da" : "Nu")).length()));

    int totalWidth=maxLength+4;
    string border(totalWidth, '-');

    cout<<"+"<<border<<"+"<<endl;
    cout<<"| Profil Pacient"<<setw(totalWidth-14)<<right<<" |"<<endl;
    cout<<"+"<<border<<"+"<<endl;
    cout<<"| Nume: "<<setw(totalWidth-7)<<left<<nume<<"|"<<endl;
    cout<<"| Prenume: "<<setw(totalWidth-10)<<left<<prenume<<"|"<<endl;
    cout<<"| Email: "<<setw(totalWidth-8)<<left<<email<<"|"<<endl;
    cout<<"| Varsta la ultimul control: "<<setw(totalWidth-28)<<left<<varsta<<"|"<<endl;
    cout<<"| Asigurat: "<<setw(totalWidth-11)<<left<<(asigurat ? "Da":"Nu")<<"|"<<endl;
    cout<<"+"<<border<<"+"<<endl;
}

void Pacient::adaugaProgramare(const string& emailMedic, int ora) {
    programari[ora]=emailMedic;
}

void Pacient::stergeProgramare(int ora) {
    programari.erase(ora);
}

void Pacient::vizualizeazaProgramari() {
    vector<Medic*> medici=readMediciFrom_CSV("medici.csv");
    map<string, pair<string, string>> mediciMap;

    for (Medic* medic:medici) {
        mediciMap[medic->getEmail()]=make_pair(medic->getNume(), medic->getPrenume());
    }

    for (const auto& programare : programari) {
        int ora=programare.first;
        string emailMedic=programare.second;

        auto it=mediciMap.find(emailMedic);
        if (it!=mediciMap.end()) {
            string numeMedic=it->second.first;
            string prenumeMedic=it->second.second;
            cout<<"Ora: "<<ora<<" - Medic: "<<numeMedic<<" "<<prenumeMedic<<endl;

        } else {
            cout<<"Eroare: Medic necunoscut"<<endl;
        }
    }
}
