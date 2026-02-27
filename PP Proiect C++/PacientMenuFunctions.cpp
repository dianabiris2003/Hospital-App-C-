#include "PacientMenuFunctions.h"

void veziProfilPacient(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        Pacient *p=readFromCSV_Pacient("pacienti.csv",email);
        p->afisareStilizata();
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: "<<endl<<endl;
        cout<<"1) Meniu principal"<<endl;
        cout<<"2) Inchidere"<<endl<<endl;
        cout<<"Optiunea dumneavoastra este: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
                displayMeniuPacient(email);
            break;
            case 2:
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
    } while (optiune!=2);
}

vector<Medic*> getMediciBySpecializare(const string& specializare) {
    vector<Medic*> medici;
    ifstream file("medici.csv");
    string line, email, nume, prenume, specializareStr, nota, grad, programari;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, nume, ',');
        getline(ss, prenume, ',');
        getline(ss, email, ',');
        getline(ss, specializareStr, ',');
        getline(ss, nota, ',');
        getline(ss, grad, ',');
        getline(ss, programari, ',');

        if (specializareStr == specializare) {
            Medic* medic=new Medic(nume, prenume,email, specializareStr, stof(nota), grad);
            map<int, string> progMap;
            stringstream programariStream(programari);
            string programare;
            while (getline(programariStream, programare, ';')) {
                stringstream progDetails(programare);
                string oraStr, emailPacient;
                getline(progDetails, oraStr, '-');
                getline(progDetails, emailPacient, '-');
                progMap[stoi(oraStr)]=emailPacient;
            }
            medic->setProgramari(progMap);
            medici.push_back(medic);
        }
    }
    file.close();
    return medici;
}

vector<int> getOreDisponibile(Medic* medic) {
    vector<int> oreDisponibile;
    for (int ora=9; ora<=16;++ora) {
        if (medic->esteDisponibil(ora)) {
            oreDisponibile.push_back(ora);
        }
    }
    return oreDisponibile;
}

void faProgramarePacient(const string& emailPacient) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        displayListaSpecializari();
        int optiuneSpecializare;
        string optiuneSpecializare_str;
        cout<<endl;
        cout<<"Alegeti specializarea sau introduceti \'0\' pentru a reveni la meniul principal : ";
        cin>>optiuneSpecializare;
        switch (optiuneSpecializare){
            case 0:
                cout<<"Se va reveni la meniul principal...";
                this_thread::sleep_for(chrono::seconds(3));
                displayMeniuPacient(emailPacient);
            case 1:
                optiuneSpecializare_str="Cardiologie";
                break;
            case 2:
                optiuneSpecializare_str="Pediatrie";
                break;
            case 3:
                optiuneSpecializare_str="Dermatologie";
                break;
            case 4:
                optiuneSpecializare_str="Neurologie";
                break;
            case 5:
                optiuneSpecializare_str="Ortopedie";
                break;
            case 6:
                optiuneSpecializare_str="Gastroenterologie";
                break;
            case 7:
                optiuneSpecializare_str="Endocrinologie";
                break;
            case 8:
                optiuneSpecializare_str="Oftalmologie";
                break;
            case 9:
                optiuneSpecializare_str="Stomatologie";
                break;
            case 10:
                optiuneSpecializare_str="Reumatologie";
                break;
            default:
                system("cls");
                cout<<"Optiunea introdusa nu este corecta!"<<endl<<endl;
                cout<<"Se va reveni la meniul principal..."<<endl;
                this_thread::sleep_for(chrono::seconds(3));
                displayMeniuPacient(emailPacient);
                break;
        }
        system("cls");
        vector<Medic*> medici=getMediciBySpecializare(optiuneSpecializare_str);
        if(medici.empty()) {
            cout<<"Ne pare rau! Momentan nu sunt medici disponibili pentru specializarea aleasa!"<<endl<<endl;
            cout<<"Va redirectionam la meniul principal...";
            this_thread::sleep_for(chrono::seconds(5));
            displayMeniuPacient(emailPacient);
        }
        for (size_t i=0; i<medici.size(); ++i) {
            cout<<i+1<<") "<<medici[i]->getNume()<<" "<<medici[i]->getPrenume()<<" - "<<medici[i]->getGrad()<<", nota: "<<medici[i]->getNota()<<endl;
        }

        int optiuneMedic;
        cout << "Alegeti medicul sau introduceti \'0\' pentru a reveni la meniul pricnipal: ";
        cin >> optiuneMedic;
        system("cls");
        if(optiuneMedic==0) {
            cout<<"Se va reveni la meniul principal...";
            this_thread::sleep_for(chrono::seconds(3));
            displayMeniuPacient(emailPacient);
        }
        Medic* medic=medici[optiuneMedic-1];

        cout<<"Programarea dureaza o ora. Va rugam sa luati in considerare acest lucru cand va programati."<<endl<<endl;
        cout<<"Ore disponibile: "<<endl<<endl;

        vector<int> oreDisponibile = getOreDisponibile(medic);
        if (oreDisponibile.empty()) {
            string red="\033[31m";
            string reset="\033[0m";
            cout<<red<<"Nu exista ore disponibile pentru acest medic."<<reset<<endl<<endl;
            cout<<"Va redirectionam la meniul principal...";
            this_thread::sleep_for(chrono::seconds(5));
            displayMeniuPacient(emailPacient);
        }

        for (size_t i=0; i<oreDisponibile.size(); ++i) {
            cout<<i+1<<") "<<oreDisponibile[i]<<":00"<<endl;
        }

        int optiuneOra;
        cout<<endl;
        cout<<"Alegeti ora sau introduceti \'0\' pentru a reveni la meniul pricnipal : ";
        cin>>optiuneOra;
        system("cls");
        if(optiuneOra==0) {
            cout<<"Se va reveni la meniul principal...";
            this_thread::sleep_for(chrono::seconds(3));
            displayMeniuPacient(emailPacient);
        }
        if (optiuneOra<0 || optiuneOra>oreDisponibile.size()) {
            int incercariIncorecteOra=0;
            while (optiuneOra<1 || optiuneOra>oreDisponibile.size() && incercariIncorecteOra<2) {
                cout<<"Optiune invalida. Va rugam reincercati!"<<endl;
                cin>>optiuneOra;
                ++incercariIncorecteOra;
            }
        }

        int oraDisp=oreDisponibile[optiuneOra-1];
        if(medic->getEmail() != emailPacient) {
            medic->adaugaProgramare(emailPacient, oraDisp);
            Pacient *pacient=readFromCSV_Pacient("pacienti.csv",emailPacient);
            pacient->adaugaProgramare(medic->getEmail(),oraDisp);
            vector<Medic*> allMedici=readMediciFrom_CSV("medici.csv");
            ofstream newFile("temp.csv");
            if (newFile.is_open()) {
                newFile<<"Nume,Prenume,Email,Specializare,Nota,Grad,Programari\n";
                for (Medic* m:allMedici) {
                    if(m->getEmail() != medic->getEmail()){
                        newFile<<m->getNume()<<","<<m->getPrenume()<<","<<m->getEmail()<<","<<m->getSpecializare()<<","<< m->getNota()<<","<<m->getGrad()<<",";
                        map<int, string> programari=m->getProgramari();
                        for (const auto& [ora, emailPacient]:programari) {
                            newFile<<ora<<"-"<<emailPacient<<";";
                        }
                        newFile<<"\n";
                    }
                    else {
                        newFile<<medic->getNume()<<","<<medic->getPrenume()<<","<<medic->getEmail()<<","<<medic->getSpecializare()<<","<< medic->getNota()<<","<<medic->getGrad()<<",";
                        map<int, string> programari=medic->getProgramari();
                        for (const auto& [ora, emailPacient]:programari) {
                            newFile<<ora<<"-"<<emailPacient<<";";
                        }
                        newFile<<"\n";
                    }
                }
                newFile.close();
                remove("medici.csv");
                rename("temp.csv", "medici.csv");
            } else {
                cout<<"Eroare la scrierea fisierului temporar."<<endl;
            }
            vector<Pacient *> allPacienti=readPacientiFrom_CSV("pacienti.csv");
            ofstream newFilePacient("temp.csv");
            if (newFilePacient.is_open()) {
                newFilePacient<<"Nume,Prenume,Email,Varsta,Asigurare,Programari\n";
                for (Pacient* p:allPacienti) {
                    if (p->getEmail() != pacient->getEmail()) {
                        newFilePacient<<p->getNume()<<","<<p->getPrenume()<<","<<p->getEmail()<<","<<p->getVarsta()<<",";
                        if(p->getAsigurat()==1) newFilePacient<<"Da"<<",";
                        else newFilePacient<<"Nu"<<",";
                        map<int, string> programari=p->getProgramari();
                        for (const auto& [ora, emailPacient]:programari) {
                            newFilePacient<<ora<<"-"<<emailPacient<<";";
                        }
                        newFilePacient<<"\n";
                    }
                    else {
                        newFilePacient<<pacient->getNume()<<","<<pacient->getPrenume()<<","<<pacient->getEmail()<<","<<pacient->getVarsta()<<",";
                        if(pacient->getAsigurat()==1) newFilePacient<<"Da"<<",";
                        else newFilePacient<<"Nu"<<",";
                        map<int, string> programari=pacient->getProgramari();
                        for (const auto& [ora, emailPacient]:programari) {
                            newFilePacient<<ora<<"-"<<emailPacient<<";";
                        }
                        newFilePacient<<"\n";
                    }
                }
                newFilePacient.close();
                remove("pacienti.csv");
                rename("temp.csv", "pacienti.csv");
            } else {
                cout<<"Eroare la scrierea fisierului temporar."<<endl;
            }
            system("cls");
            string green="\033[1;32m";
            string reset="\033[0m";
            cout<<green<<"Programare efectuata cu succes"<<reset<<endl;
        }
        else {
            system("cls");
            string purple="\033[1;35m";
            string reset="\033[0m";
            cout<<purple<<"Emailul medicului cu cel al pacientului sunt identice!"<<reset<<endl;
            cout<<"Va redirectionam spre meniul principal!";
            this_thread::sleep_for(chrono::seconds(3));
            displayMeniuPacient(emailPacient);
        }
        cout<<endl;
        cout<<"1) Inapoi la meniul principal"<<endl;
        cout<<"2) Inchidere aplicatie"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
               displayMeniuPacient(emailPacient);
                break;
            case 2:
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
    } while (optiune!=2);
}

void vizualizareProgramarePacient(const string &email) {
        int optiune;
        int incercariIncorecte=0;
        do {
            system("cls");
            Pacient *pacient=readFromCSV_Pacient("pacienti.csv",email);
            if(pacient->getProgramari().empty()) {
                string red="\033[31m";
                string reset="\033[0m";
                cout<<red<<"Nu aveti programari pentru ziua de azi!"<<reset<<endl<<endl;
                cout<<"Va redirectionam la meniul principal...";
                this_thread::sleep_for(chrono::seconds(3));
                displayMeniuPacient(email);
            }
            pacient->vizualizeazaProgramari();
            cout<<endl;
            cout<<"1) Inapoi la meniul principal"<<endl;
            cout<<"2) Inchidere aplicatie"<<endl;
            cout<<endl;
            cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
            cin>>optiune;
            switch(optiune) {
                case 1:
                    displayMeniuPacient(email);
                break;
                case 2:
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
        } while (optiune!=2);
}


void deleteContPacient(const string email) {
    string filePath="pacienti.csv";
    vector<Pacient*>pacienti=readPacientiFrom_CSV(filePath);

    auto it=remove_if(pacienti.begin(), pacienti.end(), [&email](Pacient* pacient) {
        if (pacient->getEmail()==email) {
            delete pacient;
            return true;
        }
        return false;
    });

    if (it!=pacienti.end()) {
        pacienti.erase(it, pacienti.end());
        writePacientiTo_CSV(filePath, pacienti);
        string green="\033[1;32m";
        string reset="\033[0m";
        system("cls");
        cout<<green<<"Contul a fost sters cu succes!"<<reset<<endl<<endl;
        cout<<"Va redirectionam catre meniul de logare...";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuLogare(email);
    }

    for (Pacient* pacient:pacienti) {
        delete pacient;
    }
}

void stergeProgramarePacient(const string& emailPacient) {
    Pacient* pacient=readFromCSV_Pacient("pacienti.csv", emailPacient);
    const map<int,string>&programari=pacient->getProgramari();
    if(programari.empty()) {
        string purple="\033[1;35m";
        string reset="\033[0m";
        cout<<purple<<"Nu aveti programari pentru a fi sterse!"<<reset<<endl<<endl;
        cout<<"Va redirectionam catre meniul principal...";
        this_thread::sleep_for(chrono::seconds(5));
        displayMeniuPacient(emailPacient);
        return;
    }
    system("cls");
    cout<<"Programarile dumneavoastra:"<< endl<<endl;
    int index=1;
    vector<pair<int,string>>programariList;
    for(const auto& prog:programari) {
        cout<<index++<<") Ora: "<<prog.first<<":00 - Medic: ";//<<prog.second<<endl;
        Medic *medic=readFromCSV_Medic("medici.csv", prog.second);
        cout<<medic->getNume()<<" "<<medic->getPrenume()<<endl;
        programariList.push_back(prog);
        delete medic;
    }

    cout<<endl;
    int optiune;
    cout<<"Alegeti programarea pe care doriti sa o stergeti sau introduceti '0' pentru a reveni la meniul principal: ";
    cin>>optiune;
    cout<<endl;
    system("cls");
    if(optiune==0){
        cout<<"Se va reveni la meniul principal...";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuPacient(emailPacient);
        return;
    }

    if(optiune<1 || optiune>programariList.size()) {
        string purple="\033[1;31m";
        string reset="\033[0m";
        cout<<purple<<"Optiunea introdusa nu este valida!"<<reset<<endl<<endl;
        cout<<"Va redirectionam catre meniul principal...";
        this_thread::sleep_for(chrono::seconds(5));
        displayMeniuPacient(emailPacient);
        return;
    }

    int ora=programariList[optiune-1].first;
    string emailMedic=programariList[optiune-1].second;

    vector<Pacient*> allPacienti=readPacientiFrom_CSV("pacienti.csv");
    for (Pacient* pacient:allPacienti) {
        if (pacient->getEmail()==emailPacient) {
            pacient->stergeProgramare(ora);
            break;
        }
    }
    writePacientiTo_CSV("pacienti.csv", allPacienti);
    vector<Medic*> allMedici=readMediciFrom_CSV("medici.csv");
    for (Medic* medic:allMedici) {
        if (medic->getEmail()==emailMedic) {
            medic->stergeProgramare(ora);
            break;
        }
    }
    writeMediciTo_CSV("medici.csv", allMedici);
    string green="\033[1;32m";
    string reset="\033[0m";
    cout<<green<<"Programarea a fost stearsa cu succes!"<<reset<<endl<<endl;
    cout<<"Va redirectionam catre meniul principal...";
    this_thread::sleep_for(chrono::seconds(3));
    displayMeniuPacient(emailPacient);
}
