#include "MenuFunctions.h"
#include <chrono>
#include <thread>
#include <regex>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include "MenuInterf.h"

bool isValidEmail(string email) {
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    return regex_match(email, pattern);
}

void toLower(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string floatToString(float value) {
    ostringstream out;
    out<<fixed<<setprecision(1)<<value;
    return out.str();
}

void verificaLoginPacient(const string email) {
    Pacient *p=readFromCSV_Pacient("pacienti.csv",email);
    if(p==nullptr) {
        system("cls");
        cout<<"Nu aveti cont in calitate de pacient! Doriti sa creati un cont nou?"<<endl<<endl;
        cout<<"1) Da"<<endl;
        cout<<"2) Nu"<<endl<<endl;
        int optiune;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                creareContPacient(email);
                break;
            case 2:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for(chrono::seconds(2));
                exit(0);

        }
    }
    displayMeniuPacient(email);
}

void verificaLoginMedic(const string email) {
   Medic *m=readFromCSV_Medic("medici.csv",email);
    if(m==nullptr) {
        system("cls");
        cout<<"Nu aveti cont in calitate de medic! Doriti sa creati un cont nou?"<<endl<<endl;
        cout<<"1) Da"<<endl;
        cout<<"2) Nu"<<endl<<endl;
        int optiune;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch (optiune) {
            case 1:
                    creareContMedic(email);
                    break;
            case 2:
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for (chrono::seconds(1));
                exit(0);
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                cout<<"Aplicatia se va inchide... ";
                this_thread::sleep_for(chrono::seconds(2));
                exit(0);

        }
    }
    displayMeniuMedic(email);
}

void creareContPacient(const string& email) {
    Pacient* p=readFromCSV_Pacient("pacienti.csv", email);
    if (p!=nullptr) {
        string purple="\033[1;35m";
        string reset="\033[0m";
        cout<<purple<<"Exista deja un cont cu acest email!"<<reset<<endl;
        cout<<"Va redirectionam spre meniul de logare!";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuLogare(email);
    } else {
        vector<string> date_pacient;
        string numePacient, prenumePacient, varsta_str, asigurat_str;
        int varsta;
        cout<<endl;
        cout<<"Introduceti numele dumneavoastra: ";
        cin>>numePacient;
        cout<<"Introduceti prenumele dumneavoastra: ";
        cin>>prenumePacient;
        cout<<"Introduceti varsta dumneavoastra: ";
        cin>>varsta;
        cout<<"Sunteti asigurat medical? (Da/Nu): ";
        cin>>asigurat_str;
        cout<<endl;
        date_pacient.push_back(numePacient);
        date_pacient.push_back(prenumePacient);
        date_pacient.push_back(email);
        varsta_str=to_string(varsta);
        date_pacient.push_back(varsta_str);
        toLower(asigurat_str);
        if(asigurat_str=="da") date_pacient.push_back("Da");
        else if(asigurat_str=="nu") date_pacient.push_back("Nu");
        else {
            cout<<"Datele introduse nu sunt corecte! Va rugam incercati din nou!"<<endl<<endl;
            cout<<"Sunteti asigurat medical? (Da/Nu): ";
            cin>>asigurat_str;
            cout<<endl;
            toLower(asigurat_str);
            if(asigurat_str=="da") date_pacient.push_back("Da");
            else if(asigurat_str=="nu") date_pacient.push_back("Nu");
            else{
                cout<<"Datele introduse nu sunt corecte!"<<endl<<"Aplicatia se va inchide!";
                this_thread::sleep_for(chrono::seconds(2));
                exit(0);
            }
        }
        writeToCSV_Pacient("pacienti.csv", date_pacient);

        //Pacient* newPacient=new Pacient(numePacient, prenumePacient, email, varsta, asigurat_str=="da");
        //FisaMedicala* fisa=new FisaMedicala(newPacient, vector<map<string, Medic*>>());
        //writeToCSV_FisaMedicala("fise.csv", fisa);

        string green="\033[1;32m";
        string reset="\033[0m";
        cout<<green<<"Cont creat cu succes!"<<reset<<endl;
        cout<<"Va redirectionam catre meniul principal.";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuPacient(email);
    }
}

void displayListaSpecializari() {
    cout<<"+---------------------------+"<<endl;
    cout<<"|        Specializare       |"<<endl;
    cout<<"+---------------------------+"<<endl;
    cout<<"|  1) Cardiologie           |"<<endl;
    cout<<"|  2) Pediatrie             |"<<endl;
    cout<<"|  3) Dermatologie          |"<<endl;
    cout<<"|  4) Neurologie            |"<<endl;
    cout<<"|  5) Ortopedie             |"<<endl;
    cout<<"|  6) Gastroenterologie     |"<<endl;
    cout<<"|  7) Endocrinologie        |"<<endl;
    cout<<"|  8) Oftalmologie          |"<<endl;
    cout<<"|  9) Stomatologie          |"<<endl;
    cout<<"| 10) Reumatologie          |"<<endl;
    cout<<"+---------------------------+"<<endl;
}

void displayListaGrade() {
    cout<<"+---------------------------+"<<endl;
    cout<<"|          Gradul           |"<<endl;
    cout<<"+---------------------------+"<<endl;
    cout<<"|  1) Medic rezident        |"<<endl;
    cout<<"|  2) Medic specialist      |"<<endl;
    cout<<"|  3) Medic primar          |"<<endl;
    cout<<"|  4) Profesor universitar  |"<<endl;
    cout<<"+---------------------------+"<<endl;
}

void displayListaUniveristati(){
    cout<<"+------------------------------------------------------------------------------+"<<endl;
    cout<<"|                        Studiile au fost realizate la:                        |"<<endl;
    cout<<"+------------------------------------------------------------------------------+"<<endl;
    cout<<"|  1) Universitatea de Medicina si Farmacie \"Carol Davila\" din Bucuresti       |"<<endl;
    cout<<"|  2) Universitatea de Medicina si Farmacie \"Iuliu Hatieganu\" din Cluj-Napoca  |"<<endl;
    cout<<"|  3) Universitatea de Medicina si Farmacie \"Grigore T. Popa\" din Iasi         |"<<endl;
    cout<<"|  4) Universitatea de Medicina si Farmacie din Targu Mures                    |"<<endl;
    cout<<"|  5) Universitatea de Medicina si Farmacie \"Victor Babes\" din Timisoara       |"<<endl;
    cout<<"|  6) Universitatea \"Ovidius\" din Constanta, Facultatea de Medicina            |"<<endl;
    cout<<"|  7) Universitatea de Medicina si Farmacie din Craiova                        |"<<endl;
    cout<<"|  8) Universitatea \"Lucian Blaga\" din Sibiu, Facultatea de Medicina           |"<<endl;
    cout<<"|  9) Universitatea din Oradea, Facultatea de Medicina si Farmacie             |"<<endl;
    cout<<"+------------------------------------------------------------------------------+"<<endl;
    cout<<endl;
}

void creareContMedic(const string email) {
    Medic *m=readFromCSV_Medic("medici.csv",email);
    if(m!=nullptr) {
        string purple="\033[1;35m";
        string reset="\033[0m";
        cout<<purple<<"Exista deja un cont cu acest email!"<<reset<<endl;
        cout<<"Va redirectionam spre meniul de logare!";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuLogare(email);
    }
    else {
        vector<string> date_medic;
        string numeMedic, prenumeMedic, specializare, grad, nota_str;
        float nota;
        string green="\033[1;32m";
        string reset="\033[0m";
        cout<<endl;
        cout<<"Introduceti numele dumneavoastra: ";
        cin>>numeMedic;
        cout<<"Introduceti prenumele dumneavoastra: ";
        cin>>prenumeMedic;
        system("cls");
        cout<<"Selectati specializarea dumneavoastra: ";
        cout<<endl;
        cout<<endl;
        displayListaSpecializari();
        cout<<endl;
        cout<<"Introduceti numarul corespunzator optiunii: ";
        int optiune;
        cin>>optiune;
        switch(optiune) {
            case 1:
                specializare="Cardiologie";
                break;
            case 2:
                specializare="Pediatrie";
                break;
            case 3:
                specializare="Dermatologie";
                break;
            case 4:
                specializare="Neurologie";
                break;
            case 5:
                specializare="Ortopedie";
                break;
            case 6:
                specializare="Gastroenterologie";
                break;
            case 7:
                specializare="Endocrinologie";
                break;
            case 8:
                specializare="Oftalmologie";
                break;
            case 9:
                specializare="Stomatologie";
                break;
            case 10:
                specializare="Reumatologie";
                break;
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                cout<<"Veti fi redirectionat catre pagina de logare";
                this_thread::sleep_for(chrono::seconds(2));
                displayMeniuLogare(email);
                break;
        }
        system("cls");
        cout<<"Selectati Universitatea la care ati studiat pentrua putea verifica datele dumneavoastra: ";
        cout<<endl;
        cout<<endl;
        displayListaUniveristati();
        cout<<"Introduceti numarul corespunzator optiunii: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                cout<<"Datele se verifica..."<<endl<<endl;
                this_thread::sleep_for(chrono::seconds(5));
                cout<<green<<"Datele sunt corecte, va multumim!"<<reset;
                this_thread::sleep_for(chrono::seconds(3));
                break;
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                cout<<"Veti fi redirectionat catre pagina de logare";
                this_thread::sleep_for(chrono::seconds(2));
                displayMeniuLogare(email);
                break;
        }
        system("cls");
        nota=0.0;
        cout<<"Selectati gradul dumneavoastra: "<<endl<<endl;
        displayListaGrade();
        cout<<endl;
        cout<<"Introduceti numarul corespunzator optiunii: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
                grad="Medic rezident";
                break;
            case 2:
                grad="Medic specialist";
                break;
            case 3:
                grad="Medic primar";
                break;
            case 4:
                grad="Profesor universitar";
                break;
            default:
                cout<<"Optiunea introdusa nu este corecta!"<<endl;
                cout<<"Veti fi redirectionat catre pagina de logare";
                this_thread::sleep_for(chrono::seconds(2));
                displayMeniuLogare(email);
                break;
        }
        date_medic.push_back(numeMedic);
        date_medic.push_back(prenumeMedic);
        date_medic.push_back(email);
        date_medic.push_back(specializare);
        nota_str=floatToString(nota);
        date_medic.push_back(nota_str);
        date_medic.push_back(grad);
        date_medic.push_back("");
        writeToCSV_Medic("medici.csv",date_medic);
        system("cls");
        cout<<green<<"Cont creat cu succes!"<<reset<<endl;
        cout<<"Va redirectionam catre meniul principal.";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuMedic(email);
    }
}


