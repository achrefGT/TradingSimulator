#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "Transaction.h"
#include "Portefeuille.h"
#include "Date.h"
#include <random>
#include <cmath>

using namespace std;
class Trader {
    public :
        virtual Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille)=0;

};

class TraderAleatoire : public Trader {
    public :
        Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);

} ;

Transaction TraderAleatoire::choisirTransaction(const Bourse& bourse, const Portefeuille& portefeuille) {
    Transaction tx;
    vector<PrixJournalier> actionsDisponibles = bourse.getPrixJournaliersParDate(bourse.getDateAujourdHui(), portefeuille.getSolde()); // avoir une copie des prix journaliers disponibles
    vector<Titre> titresDisponibles = portefeuille.getTitres();
    int choix = rand() % 3;
    if (actionsDisponibles.empty()) {
        choix = rand() % 2;   // si il n'y a pas des actions dans la bourse soit on vend des titres, soit on fait rien
    }
    if (titresDisponibles.empty()) {
        choix = 2;           // si le portefeuille est vide on achete
    }
    if (actionsDisponibles.empty() && titresDisponibles.empty()) return Transaction ();
    typeTransaction type = rien;
    int i = 0, taille = 0, quantite = 0;
    switch (choix) {
        case 0:
            type = rien;
            break;
        case 1:
            type = vente;
            taille = titresDisponibles.size();
            i = rand() % taille;
            quantite = 1 + rand() % (titresDisponibles[i].getQuantite()); // la quantite a vendre ne doit pas dépasser ce qu'il y a dans le portefeuille
            return Transaction(Titre(titresDisponibles[i].getNomAction(), quantite), type);
        case 2:
            type = achat;
            taille = actionsDisponibles.size();
            i = rand() % taille;
            int quantiteMax = ceil(portefeuille.getSolde()/actionsDisponibles[i].getPrix());
            do{
                i = rand() % taille;
                quantiteMax = ceil(portefeuille.getSolde()/actionsDisponibles[i].getPrix());
            }while(quantiteMax<1);

            quantite = 1+ rand() % quantiteMax;
            return Transaction(Titre(actionsDisponibles[i].getNomAction(), quantite), type);
    }
    return tx;
}


#endif // TRADER_H_INCLUDED

