#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "Transaction.h"
#include "Portefeuille.h"
#include "Date.h"
#include <random>

using namespace std;

class Trader {
    public :
        virtual Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);

};

class TraderAleatoire : public Trader {
    public :
        Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);

} ;

Transaction TraderAleatoire::choisirTransaction(const Bourse& bourse, const Portefeuille& portefeuille) {
    vector<PrixJournalier> actionsDisponibles = bourse.getPrixJournaliersParDate(bourse.getDateFinRecherche(), portefeuille.getSolde()); // avoir une copie des prix journaliers disponibles
    int choix = rand() % 3;
    if (actionsDisponibles.empty()) {
        choix = rand() % 2;   // si il n'y a pas des actions dans la bourse soit on vend des titres ou on fait rien
    }
    if (portefeuille.getTitres().empty()) {
        choix = 2;           // si le portefeuille est vide on achete
    }
    typeTransaction type = rien;
    int i = 0, taille = 0, quantite = 0;
    switch (choix) {
        case 0:
            type = rien;
            break;
        case 1:
            type = vente;
            taille = portefeuille.getTitres().size();
            i = rand() % taille;
            quantite = 1 + rand() % (portefeuille.getTitres()[i].getQuantite()); // la quantite a vendre ne doit pas dépasser ce qu'il y a dans la portefeuille
            break;
        case 2:
            type = achat;
            taille = actionsDisponibles.size();
            i = rand() % taille;
            do {
                quantite = 1 + rand() % 100;
            } while (quantite * actionsDisponibles[i].getPrix() > portefeuille.getSolde()); // il faut pas depasser le solde dans le portefeuille
            break;
    }
    return Transaction(actionsDisponibles[i].getNomAction(), quantite, type);
}

#endif // TRADER_H_INCLUDED
