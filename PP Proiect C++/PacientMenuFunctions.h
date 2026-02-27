#ifndef PACIENTMENUFUNCTIONS_H
#define PACIENTMENUFUNCTIONS_H

#include "MenuFunctions.h"
#include <chrono>
#include <thread>
#include <regex>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include "MenuInterf.h"

void veziProfilPacient(const string email);
void faProgramarePacient(const string& emailPacient);
void stergeProgramarePacient(const string& emailPacient);
void vizualizareProgramarePacient(const string &email);
void deleteContPacient(const string email);
#endif //PACIENTMENUFUNCTIONS_H
