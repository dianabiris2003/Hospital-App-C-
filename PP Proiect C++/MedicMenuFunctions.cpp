#include "MedicMenuFunctions.h"


void veziProfilMedic(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        Medic *m=readFromCSV_Medic("medici.csv",email);
        m->afisareStilizata();
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: "<<endl<<endl;
        cout<<"1) Meniu principal"<<endl;
        cout<<"2) Inchidere"<<endl<<endl;
        cout<<"Optiunea dumneavoastra este: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
                displayMeniuMedic(email);
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

void veziProgramareMedic(const string email) {
    int optiune;
    int incercariIncorecte=0;
    do {
        system("cls");
        Medic *medic=readFromCSV_Medic("medici.csv",email);
        if(medic->getProgramari().empty()) {
            string red="\033[31m";
            string reset="\033[0m";
            cout<<red<<"Nu aveti programari pentru ziua de azi!"<<reset<<endl<<endl;
            cout<<"Va redirectionam la meniul principal...";
            this_thread::sleep_for(chrono::seconds(3));
            displayMeniuMedic(email);
        }
        medic->vizualizeazaProgramari();
        cout<<endl;
        cout<<"1) Inapoi la meniul principal"<<endl;
        cout<<"2) Inchidere aplicatie"<<endl;
        cout<<endl;
        cout<<"Va rugam selectati operatiunea pe care doriti sa o efectuati: ";
        cin>>optiune;
        switch(optiune) {
            case 1:
                displayMeniuMedic(email);
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

void deleteContMedic(const string email) {
    string filePath="medici.csv";
    vector<Medic*> medici=readMediciFrom_CSV(filePath);

    auto it=remove_if(medici.begin(), medici.end(), [&email](Medic* medic) {
        if(medic->getEmail()==email) {
            delete medic;
            return true;
        }
        return false;
    });

    if (it!=medici.end()) {
        medici.erase(it, medici.end());
        writeMediciTo_CSV(filePath, medici);
        string green="\033[1;32m";
        string reset="\033[0m";
        system("cls");
        cout<<green<<"Contul a fost sters cu succes!"<<reset<<endl;
        cout<<"Va redirectionam catre meniul de logare...";
        this_thread::sleep_for(chrono::seconds(3));
        displayMeniuLogare(email);
    }
    for (Medic* medic:medici) {
        delete medic;
    }
}
vector<Pacient*> medicGetPacienti(const string& filename, const string& emailMedic) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Eroare la deschiderea fișierului " << filename << endl;
        exit(0);
    }
    vector<Pacient*> pacienti;
    string line;
    while (getline(file, line)) {
        Pacient* pacient;
        stringstream ss(line);
        string email, diagnosticeStr;

        getline(ss, email, ',');
        getline(ss, diagnosticeStr, ',');
        stringstream ss_diag(diagnosticeStr);
        string diagnostic;
        while (getline(ss_diag, diagnostic, ';')) {
            stringstream diagDetails(diagnostic);
            string diag, emailMedic_str;
            getline(diagDetails, diag, '-');
            getline(diagDetails, emailMedic_str, '-');
            if (emailMedic == emailMedic_str) {
                pacient = readFromCSV_Pacient("pacienti.csv", email);
            }
        }
        if (pacient != nullptr) {
            pacienti.push_back(pacient);
        }
    }

    file.close();
    return pacienti;
}

void veziPacienti(const string& emailMedic) {
    int optiune;
    vector<Pacient*> pacienti = medicGetPacienti("fise.csv", emailMedic);
    int index = 1;
    for (const auto& pacient : pacienti) {
        cout << index++ << ") " << pacient->getNume() << " " << pacient->getPrenume() << endl;
    }
    this_thread::sleep_for(chrono::seconds(0));
    cout<<endl;
    cout << "Va rugam selectati pacientul pentru a vedea detalii despre acesta sau '0' pentru a reveni la meniul principal: ";
    cin >> optiune;

    system("cls");

    if (optiune >= 1 && optiune <= pacienti.size()) {
        pacienti[optiune - 1]->afisareStilizata();
        this_thread::sleep_for(chrono::seconds(10));
    } else if (optiune == 0) {
        cout << "Revenire la meniul principal..." << endl;
        displayMeniuMedic(emailMedic);
    } else {
        cout << "Optiune invalida. Revenire la meniul principal..." << endl;
        displayMeniuMedic(emailMedic);
    }

}
