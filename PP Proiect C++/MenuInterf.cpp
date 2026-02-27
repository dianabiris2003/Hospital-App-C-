#include "MenuInterf.h"
#include "MenuFunctions.h"
#include <chrono>
#include <thread>

#include "FileIO.h"
#include "PacientMenuFunctions.h"
#include "MedicMenuFunctions.h"

void displayMeniuLogare(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        cout<<"+--------------------------------------+"<<endl;
        cout<<"|           Meniu de logare            |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<"| 1) Logare                            |"<<endl;
        cout<<"| 2) Creare cont                       |"<<endl;
        cout<<"| 3) Inchidere                         |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                displayMeniuAlegere(email);
                break;
            case 2:
                displayMeniuAlegereCreare(email);
                break;
            case 3:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                incercariIncorecte++;
                if (incercariIncorecte>=2) {
                    cout<<"Ati introdus de doua ori o optiune incorecta. Aplicatia se va inchide..."<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    exit(0);
                }
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    } while (optiune!=3);
}

void displayMeniuMedic(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        cout<<"+----------------------------------------------+"<<endl;
        cout<<"|           Meniu principal - Medic            |"<<endl;
        cout<<"+----------------------------------------------+"<<endl;
        cout<<"| 1) Vizualizare programari                    |"<<endl;
        cout<<"| 2) Vizualizare pacienti                      |"<<endl;
        cout<<"| 3) Scrie o reteta                            |"<<endl;
        cout<<"| 4) Vezi profilul tau                         |"<<endl;
        cout<<"| 5) Stergere cont                             |"<<endl;
        cout<<"| 6) Inchidere                                 |"<<endl;
        cout<<"+----------------------------------------------+"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                veziProgramareMedic(email);
                break;
            case 2:
                veziPacienti(email);
                break;
            case 3:
                break;
            case 4:
                veziProfilMedic(email);
                break;
            case 5:
                deleteContMedic(email);
            case 6:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                incercariIncorecte++;
                if (incercariIncorecte>=2) {
                    cout<<"Ati introdus de doua ori o optiune incorecta. Aplicatia se va inchide..."<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    exit(0);
                }
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    } while (optiune!=5);
}

void displayMeniuPacient(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        cout<<"+------------------------------------------------+"<<endl;
        cout<<"|           Meniu principal - Pacient            |"<<endl;
        cout<<"+------------------------------------------------+"<<endl;
        cout<<"| 1) Vezi programarile tale                      |"<<endl;
        cout<<"| 2) Programeaza-te                              |"<<endl;
        cout<<"| 3) Vizualizare fisa medicala                   |"<<endl;
        cout<<"| 4) Vizualizare retete                          |"<<endl;
        cout<<"| 5) Lasa o nota medicului tau                   |"<<endl;
        cout<<"| 6) Vezi profilul tau                           |"<<endl;
        cout<<"| 7) Sterge o programare                         |"<<endl;
        cout<<"| 8) Sterge contul                               |"<<endl;
        cout<<"| 9) Inchidere                                   |"<<endl;
        cout<<"+------------------------------------------------+"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                vizualizareProgramarePacient(email);
                break;
            case 2:
                faProgramarePacient(email);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                veziProfilPacient(email);
                this_thread::sleep_for(chrono::seconds(10));
                break;
            case 7:
                stergeProgramarePacient(email);
                break;
            case 8:
                deleteContPacient(email);
                break;
            case 9:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                incercariIncorecte++;
                if (incercariIncorecte>=2) {
                    cout<<"Ati introdus de doua ori o optiune incorecta. Aplicatia se va inchide..."<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    exit(0);
                }
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    } while (optiune!=7);
}
void displayMeniuAlegere(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        cout<<"+--------------------------------------+"<<endl;
        cout<<"|     Va conectati in calitate de:     |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<"| 1) Pacient                           |"<<endl;
        cout<<"| 2) Medic                             |"<<endl;
        cout<<"| 3) Inchidere                         |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                verificaLoginPacient(email);
                break;
            case 2:
                verificaLoginMedic(email);
                break;
            case 3:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                incercariIncorecte++;
                if (incercariIncorecte>=2) {
                    cout<<"Ati introdus de doua ori o optiune incorecta. Aplicatia se va inchide..."<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    exit(0);
                }
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    } while (optiune!=3);
}
void displayMeniuAlegereCreare(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        cout<<"+--------------------------------------+"<<endl;
        cout<<"|    Va creati cont in calitate de:    |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<"| 1) Pacient                           |"<<endl;
        cout<<"| 2) Medic                             |"<<endl;
        cout<<"| 3) Inchidere                         |"<<endl;
        cout<<"+--------------------------------------+"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                creareContPacient(email);
                break;
            case 2:
                creareContMedic(email);
                break;
            case 3:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                incercariIncorecte++;
                if (incercariIncorecte>=2) {
                    cout<<"Ati introdus de doua ori o optiune incorecta. Aplicatia se va inchide..."<<endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    exit(0);
                }
                this_thread::sleep_for(chrono::seconds(1));
                break;
        }
    } while (optiune!=3);
}

