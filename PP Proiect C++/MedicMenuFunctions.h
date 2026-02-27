#ifndef MEDICMENUFUNCTIONS_H
#define MEDICMENUFUNCTIONS_H

#include "MenuFunctions.h"
#include <chrono>
#include <thread>
#include <regex>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include "MenuInterf.h"
#include "FileIO.h"

void veziProfilMedic(const string email);
void veziProgramareMedic(const string email);
vector<Pacient*>medicGetPacienti(const string & filename, const string &emailMedic);
void veziPacienti(const string &email);
//void puneDiagnostic()
void deleteContMedic(const string email);

#endif //MEDICMENUFUNCTIONS_H
