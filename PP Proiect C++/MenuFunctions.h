#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include <iostream>
#include <string>
#include "Pacient.h"
#include "FileIO.h"
using namespace std;

//Functii pentru meniul de logare
void verificaLoginPacient(const string email);
void verificaLoginMedic(const string email);
void creareContPacient(const string &email);
void creareContMedic(const string email);
void displayListaSpecializari();
void displayListaGrade();
string floatToString(float value);
bool isValidEmail(string email);



#endif //MENUFUNCTIONS_H
