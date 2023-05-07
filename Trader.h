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
    if (actionsDisponibles.empty() && titresDisponibles.empty()) return tx;
    int choix = rand() % 3;
    if (actionsDisponibles.empty()) {
        choix = 0;   // si il n'y a pas des actions dans la bourse on fait rien
    }
    if (titresDisponibles.empty()) {
        choix = 2;           // si le portefeuille est vide on achete
    }
    if (portefeuille.getSolde()<2 && !titresDisponibles.empty())
    {
        choix = 1;
    }
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

class TraderMoyenne : public Trader {
    private :
        static map<string,vector<double>> actions;
    public :
        Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);
        double calculerMoyenne(const vector<double>&) const;
        double pourcentage(double,double) const;
} ;

map<string,vector<double>> TraderMoyenne::actions;


double TraderMoyenne::calculerMoyenne(const vector<double>& valeurs) const {
    double somme = 0.0;
    for (const auto& valeur : valeurs) {
        somme += valeur;
    }
    return somme / valeurs.size();
}

double TraderMoyenne::pourcentage(double d1,double d2) const{
    return ((d1-d2)/d1)*100.0;
}

Transaction TraderMoyenne::choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille){
    Transaction tx;
    vector<PrixJournalier> actionsDisponibles = bourse.getPrixJournaliersParDate(bourse.getDateAujourdHui(), portefeuille.getSolde()); // avoir une copie des prix journaliers disponibles
    vector<Titre> titresDisponibles = portefeuille.getTitres();
    if (actionsDisponibles.empty() && titresDisponibles.empty()) return tx;
    for (PrixJournalier pj : bourse.getHistorique()){
        if (pj.getDate() < bourse.getDateAujourdHui()){
            actions[pj.getNomAction()].push_back(pj.getPrix());
        }
    }

    tuple<typeTransaction, string, double, float> benefitMax = make_tuple(rien, "", 0.0, 0.0);
    for (PrixJournalier pj : actionsDisponibles){
        auto action = actions.find(pj.getNomAction());
        double prixMoyen;
        float pourcent;
        if ( action != actions.end() ){
            prixMoyen = this->calculerMoyenne(action->second);
           // cout<<pj.getNomAction()<<" : "<<prixMoyen<<"          "<<pj.getPrix()<<endl;
            if (prixMoyen > pj.getPrix()){
                pourcent = pourcentage(prixMoyen,pj.getPrix());
                benefitMax = (pourcent >= 2 && pourcent >= get<3>(benefitMax)) ? make_tuple(achat, pj.getNomAction(), pj.getPrix(), pourcent) : benefitMax;
            }
            else if (prixMoyen < pj.getPrix() && portefeuille.chercherTitre(pj.getNomAction()) ) {
                pourcent = -1 * pourcentage(prixMoyen,pj.getPrix());
                benefitMax = (pourcent >= 2 && pourcent >= get<3>(benefitMax)) ? make_tuple(vente, pj.getNomAction(), pj.getPrix(), pourcent) : benefitMax;
            }

        }
    }
    if (get<0>(benefitMax)==achat) return Transaction(Titre(get<1>(benefitMax),ceil((get<3>(benefitMax)/100)*portefeuille.getSolde()/get<2>(benefitMax))),achat);
    if (get<0>(benefitMax)==vente) return Transaction(Titre(get<1>(benefitMax),ceil((get<3>(benefitMax)/100)*portefeuille.getQuantiteTitre(get<1>(benefitMax)))),vente);

    return tx;
}


#endif // TRADER_H_INCLUDED

