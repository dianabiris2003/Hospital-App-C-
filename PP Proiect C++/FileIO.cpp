#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "Pacient.h"
#include "Medic.h"
#include "FisaMedicala.h"


using namespace std;

// Funcții de scriere în fișiere cu smart pointers

void writeToCSV_Pacient(const string& filePath, const vector<string>& date_pacient) {
    ofstream fout(filePath, ios::app);
    if (!fout.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return;
    }
    for (size_t i = 0; i < date_pacient.size(); ++i) {
        fout << date_pacient[i];
        if (i != date_pacient.size() - 1)
            fout << ",";
    }
    fout << "\n";
}

void writeToCSV_Medic(const string& filePath, const vector<string>& date_medic) {
    ofstream fout(filePath, ios::app);
    if (!fout.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return;
    }
    for (size_t i = 0; i < date_medic.size(); ++i) {
        fout << date_medic[i];
        if (i != date_medic.size() - 1)
            fout << ",";
    }
    fout << "\n";
}

void writeToCSV_FisaMedicala(const string& filename, const FisaMedicala* fisa) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << fisa->getEmailPacient() << ",";

        for (const auto& entry : fisa->getDiagnostice()) {
            file << entry.first << ";" << entry.second->getEmail() << ";";
        }

        file << "\n";
    } else {
        cout << "Eroare la deschiderea fisierului: " << filename << endl;
    }
}

// Funcții de citire din fișiere cu smart pointers

unique_ptr<Pacient> readFromCSV_Pacient(const string& filePath, const string& email) {
    ifstream fin(filePath);
    if (!fin.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return nullptr;
    }

    string line;
    getline(fin, line); // Ignorăm prima linie (header-ul)

    while (getline(fin, line)) {
        stringstream ss(line);
        string numePacient, prenumePacient, emailPacient, varsta_str, asigurat_str, programariStr;
        getline(ss, numePacient, ',');
        getline(ss, prenumePacient, ',');
        getline(ss, emailPacient, ',');
        if (emailPacient == email) {
            int varsta;
            bool asigurat;
            getline(ss, varsta_str, ',');
            getline(ss, asigurat_str, ',');
            varsta = stoi(varsta_str);
            asigurat = (asigurat_str == "Da");
            unique_ptr<Pacient> pacient = make_unique<Pacient>(numePacient, prenumePacient, emailPacient, varsta, asigurat);
            getline(ss, programariStr, ',');
            stringstream programariStream(programariStr);
            string programare;
            map<int, string> programari;
            while (getline(programariStream, programare, ';')) {
                stringstream progDetails(programare);
                string oraStr, emailMedic;
                getline(progDetails, oraStr, '-');
                getline(progDetails, emailMedic, '-');
                if (!oraStr.empty() && !emailMedic.empty()) {
                    programari[stoi(oraStr)] = emailMedic;
                }
            }

            pacient->setProgramari(programari);
            fin.close();
            return pacient;
        }
    }

    fin.close();
    return nullptr;
}

unique_ptr<Medic> readFromCSV_Medic(const string& filePath, const string& email) {
    ifstream fin(filePath);
    if (!fin.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return nullptr;
    }

    string line;
    getline(fin, line); // Ignorăm prima linie (header-ul)

    while (getline(fin, line)) {
        stringstream ss(line);
        string numeMedic, prenumeMedic, emailMedic, specializare, nota_str, grad, programariStr;
        getline(ss, numeMedic, ',');
        getline(ss, prenumeMedic, ',');
        getline(ss, emailMedic, ',');
        if (emailMedic == email) {
            float nota;
            getline(ss, specializare, ',');
            getline(ss, nota_str, ',');
            nota = stof(nota_str);
            getline(ss, grad, ',');
            unique_ptr<Medic> medic = make_unique<Medic>(numeMedic, prenumeMedic, emailMedic, specializare, nota, grad);
            getline(ss, programariStr, ',');
            stringstream programariStream(programariStr);
            string programare;
            map<int, string> programari;
            while (getline(programariStream, programare, ';')) {
                stringstream progDetails(programare);
                string oraStr, emailPacient;
                getline(progDetails, oraStr, '-');
                getline(progDetails, emailPacient, '-');
                if (!oraStr.empty() && !emailPacient.empty()) {
                    programari[stoi(oraStr)] = emailPacient;
                }
            }

            medic->setProgramari(programari);
            fin.close();
            return medic;
        }
    }

    fin.close();
    return nullptr;
}

FisaMedicala* readFromCSV_Fisa(string filename, string emailPacient) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fișierului " << filename << endl;
        return nullptr;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string email, diagnosticeStr;

        getline(ss, email, ',');

        if (email == emailPacient) {
            getline(ss, diagnosticeStr, ',');

            stringstream ss_diag(diagnosticeStr);
            string diagnostic;
            map<string, unique_ptr<Medic>> diagnosticCuMedic;

            while (getline(ss_diag, diagnostic, ';')) {
                stringstream diagDetails(diagnostic);
                string diag, emailMedic;
                getline(diagDetails, diag, '-');
                getline(diagDetails, emailMedic, '-');

                if (!emailMedic.empty()) {
                    unique_ptr<Medic> medic = readFromCSV_Medic("medici.csv",emailMedic); // Funcție pentru a citi Medic utilizând unique_ptr
                    if (medic != nullptr) {
                        diagnosticCuMedic[diag] = move(medic);
                    } else {
                        cout << "Eroare la citirea medicului cu email " << emailMedic << endl;
                    }
                }
            }

            file.close();
            return new FisaMedicala(emailPacient, move(diagnosticCuMedic));
        }
    }

    file.close();
    return nullptr;
}


vector<unique_ptr<Medic>> readMediciFrom_CSV(const string& filePath) {
    vector<unique_ptr<Medic>> medici;
    ifstream file(filePath);
    string line, email, nume, prenume, specializareStr, nota, grad, programari;
    getline(file, line); // Ignorăm prima linie (header-ul)

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, nume, ',');
        getline(ss, prenume, ',');
        getline(ss, email, ',');
        getline(ss, specializareStr, ',');
        getline(ss, nota, ',');
        getline(ss, grad, ',');
        getline(ss, programari, ',');

        unique_ptr<Medic> medic = make_unique<Medic>(nume, prenume, email, specializareStr, stof(nota), grad);
        stringstream programariStream(programari);
        string programare;
        map<int, string> progMap;
        while (getline(programariStream, programare, ';')) {
            stringstream progDetails(programare);
            string oraStr, emailPacient;
            getline(progDetails, oraStr, '-');
            getline(progDetails, emailPacient, '-');
            if (!oraStr.empty() && !emailPacient.empty()) {
                progMap[stoi(oraStr)] = emailPacient;
            }
        }
        medic->setProgramari(progMap);
        medici.push_back(move(medic));
    }
    file.close();
    return medici;
}

vector<unique_ptr<Pacient>> readPacientiFrom_CSV(const string& filePath) {
    vector<unique_ptr<Pacient>> pacienti;
    ifstream file(filePath);
    string line, email, nume, prenume, varstaStr, asigurare, programari;

    getline(file, line); // Ignorăm prima linie (header-ul)

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, nume, ',');
        getline(ss, prenume, ',');
        getline(ss, email, ',');
        getline(ss, varstaStr, ',');
        getline(ss, asigurare, ',');
        getline(ss, programari, ',');

        bool asigurareBool = (asigurare == "Da");
        unique_ptr<Pacient> pacient = make_unique<Pacient>(nume, prenume, email, stoi(varstaStr), asigurareBool);
        stringstream programariStream(programari);
        string programare;
        map<int, string> progMap;
        while (getline(programariStream, programare, ';')) {
            stringstream progDetails(programare);
            string oraStr, emailMedic;
            getline(progDetails, oraStr, '-');
            getline(progDetails, emailMedic, '-');
            if (!oraStr.empty() && !emailMedic.empty()) {
                progMap[stoi(oraStr)] = emailMedic;
            }
        }
        pacient->setProgramari(progMap);
        pacienti.push_back(move(pacient));
    }
    file.close();
    return pacienti;
}

void writeMediciTo_CSV(const string& filePath, const vector<unique_ptr<Medic>>& medici) {
    ofstream fout(filePath);
    if (!fout.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return;
    }
    fout << "Nume,Prenume,Email,Specializare,Nota,Grad,Programari\n";
    for (const auto& medic : medici) {
        fout << medic->getNume() << "," << medic->getPrenume() << "," << medic->getEmail() << "," << medic->getSpecializare() << "," << medic->getNota() << "," << medic->getGrad() << ",";
        const auto& programari = medic->getProgramari();
        for (const auto& prog : programari) {
            fout << prog.first << "-" << prog.second << ";";
        }
        fout << "\n";
    }
    fout.close();
}

void writePacientiTo_CSV(const string& filePath, const vector<unique_ptr<Pacient>>& pacienti) {
    ofstream fout(filePath);
    if (!fout.is_open()) {
        cout << "Eroare la deschiderea fisierului: " << filePath << endl;
        return;
    }
    fout << "Nume,Prenume,Email,Varsta,Asigurat,Programari\n";
    for (const auto& pacient : pacienti) {
        fout << pacient->getNume() << "," << pacient->getPrenume() << "," << pacient->getEmail() << "," << pacient->getVarsta() << "," << (pacient->getAsigurat() ? "Da" : "Nu") << ",";
        const auto& programari = pacient->getProgramari();
        for (const auto& prog : programari) {
            fout << prog.first << "-" << prog.second << ";";
        }
        fout << "\n";
    }
    fout.close();
}
