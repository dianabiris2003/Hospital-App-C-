#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>
#include "Pacient.h"


using namespace std;
#ifndef FILEIO_H
#define FILEIO_H

// functii de scriere in csv
void writeToCSV_Pacient(const string& filePath, const vector<string>& date_pacient);
void writeToCSV_Medic(const string& filePath, const vector<string>& date_medic);
void writeToCSV_FisaMedicala(const string& filename, const FisaMedicala* fisa);

unique_ptr<Pacient> readFromCSV_Pacient(const string& filePath, const string& email);
unique_ptr<Medic> readFromCSV_Medic(const string& filePath, const string& email);
unique_ptr<FisaMedicala> readFromCSV_Fisa(const string& filename, const string& emailPacient);

vector<unique_ptr<Medic>> readMediciFrom_CSV(const string& filePath);
vector<unique_ptr<Pacient>> readPacientiFrom_CSV(const string& filePath);

void writeMediciTo_CSV(const string& filePath, const vector<unique_ptr<Medic>>& medici);
void writePacientiTo_CSV(const string& filePath, const vector<unique_ptr<Pacient>>& pacienti);







#endif //FILEIO_H
