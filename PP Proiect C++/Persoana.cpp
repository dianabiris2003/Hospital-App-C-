#include "Persoana.h"
Persoana::Persoana(string nume, string prenume, string email){
    this->nume=nume;
    this->prenume=prenume;
    this->email=email;
}

Persoana::Persoana(){
    this->nume="Necunoscut";
    this->prenume="Necunoscut";
    this->email="Necunoscut";
}

void Persoana::afisare(){
    cout<<"Nume: "<<this->nume<<endl;
    cout<<"Prenume: "<<this->prenume<<endl;
    cout<<"Email: "<<this->email<<endl;
}