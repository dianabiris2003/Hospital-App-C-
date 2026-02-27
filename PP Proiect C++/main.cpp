#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include "Persoana.h"
#include "Pacient.h"
#include "Medic.h"
#include "MenuInterf.h"
#include "FileIO.h"
#include "MenuFunctions.h"
using namespace std;
int main(int argc, char* argv[]){
    if(argc!=3) {
        cout<<"Nu ati introdus suficiente argumente! Va rugam reincercati!"<<endl;
        this_thread::sleep_for(chrono::seconds(3));
        exit(0);
    }
    if(string(argv[1])!="login") {
        cout<<"Nu ati introdus comanda coresounzatoare (login)! Va rugam sa verificati!";
        this_thread::sleep_for(chrono::seconds(3));
        exit(0);
    }
    if(!isValidEmail(string(argv[2]))) {
        cout<<"Emailul nu este valid!"<<endl;
        this_thread::sleep_for(chrono::seconds(2));
        exit(0);
    }
    displayMeniuLogare(string(argv[2]));

    system("pause");
}
