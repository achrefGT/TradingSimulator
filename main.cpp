#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "Bourse.h"
#include "Date.h"
#include "PrixJournalier.h"
#include "PersistancePrixJournalier.h"

using namespace std;


int main(){

    Date d1(4, 9, 2023);
    Date d2(31, 12, 2022);
    Date d3(28, 2, 2021);
    Date d4(29, 2, 2020);
    Date d5(0,0,0);
    cout << "donner la Date (format: jour/mois/annee) -> " ;
    cin >> d5;
    cout << "Date 1: " << d1 <<"\nDate 2: "<<d2<<"\nDate 3: "<< d3 <<"\nDate 4: "<< d4 <<"\nDate 5: "<<d5<< endl;
    cout << "**************************************************\n";
    cout << "Date 1 is equal to Date 2: " << (d1 == d2) << endl;
    cout << "Date 1 is equal to Date 3: " << (d1 == d3) << endl;
    cout << "Date 1 is less than Date 2: " << (d1 < d2) << endl;
    cout << "Date 1 is less than Date 3: " << (d1 < d3) << endl;
    cout << "Date 1 is greater than Date 2: " << (d1 > d2) << endl;
    cout << "Date 1 is greater than Date 3: " << (d1 > d3) << endl;
    cout << "**************************************************\n";

    d1.incrementerDate();
    cout << "Date 1 after incrementing -> " << d1 << endl;
    d2.incrementerDate();
    cout << "Date 2 after incrementing -> " << d2 << endl;
    d3.incrementerDate();
    cout << "Date 3 after incrementing-> " << d3 << endl;
    d4.incrementerDate();
    cout << "Date 4 after incrementing -> " << d4 << endl;
    d5.incrementerDate();
    cout << "Date 5 after incrementing -> " << d5 << endl;

    cout << "**************************************************\n";
    PersistancePrixJournaliers ppj;
    Date dateFinRecherche(16, 4, 2022);
    BourseVector bourse(dateFinRecherche,ppj.lirePrixJournaliersDUnFichier("prices_simple.csv"));

    Date date(4, 1, 2010);
    vector<string> actionsDisponibles = bourse.getActionsDisponiblesParDate(date);
    cout << "Available stocks on : " << date << ":" <<endl;
    if (actionsDisponibles.size()==0) {
            cout << "  pas des actions pour cette date " << endl;
    }
    else {
        for (string action : actionsDisponibles) {
            cout << " - " << action << endl;
        }
    }

    date = Date(1, 1, 2023);
    vector<PrixJournalier> prixJournaliers = bourse.getPrixJournaliersParDate(date);
    cout << "PrixJournalier objects for " << date << ":" <<endl;
    if (prixJournaliers.size()==0) {
            cout << "  pas des prix journaliers pour cette date " << endl;
    }
    else {
        for (PrixJournalier prix : prixJournaliers) {
            cout << " - " << prix << endl;
        }
    }


    vector<PrixJournalier> historique = bourse.getHistorique();
    cout << " l'historique pour cette bourse :"<<endl; // 9 premiers prix journaliers
    for (PrixJournalier prix : historique) {
        cout << "Date: " << prix.getDate() << " | Nom d'action: "  << prix.getNomAction() <<" | Prix: " << prix.getPrix() << endl;
    }
return 0;
}

