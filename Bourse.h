#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "Date.h"
#include "PrixJournalier.h"
#include "PersistancePrixJournalier.h"

using namespace std;



class Bourse {
    protected:
        Date dateFinRecherche;
    public:
        Bourse(Date dFR) : dateFinRecherche(dFR) {};
        Date getDateFinRecherche() const ;
        virtual vector<string> getActionsDisponiblesParDate(Date,double prixMax = 0.0) const = 0;
        virtual vector<PrixJournalier> getPrixJournaliersParDate(Date,double prixMax = 0.0) const = 0;
};

Date Bourse::getDateFinRecherche() const{
    return dateFinRecherche;
}


class BourseVector : public Bourse {
    private:
        vector<PrixJournalier> historique;
    public:
        BourseVector(Date dFR,vector<PrixJournalier> vect) : Bourse(dFR),historique(vect) {};
        vector<string> getActionsDisponiblesParDate(Date,double) const;
        vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
        vector<PrixJournalier> getHistorique() const;
};

vector<PrixJournalier> BourseVector::getHistorique() const {
    return historique;
    }


vector<string> BourseVector::getActionsDisponiblesParDate(Date date,double prixMax=0.0) const{
    vector<string> actionsDisponibles;
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= date) {
            if ((prixMax && pj.getPrix()>=prixMax) || !prixMax){
                actionsDisponibles.push_back(pj.getNomAction());
            }
        }
    }
    return actionsDisponibles;
}

vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(Date date,double prixMax=0.0) const{
    vector<PrixJournalier> prixJournaliers;
    for (const PrixJournalier& pj : historique){
        if (pj.getDate() <= date) {
            if ((prixMax && pj.getPrix() >=prixMax) || !prixMax){
                prixJournaliers.push_back(pj);
            }
        }
    }
    return prixJournaliers;
}


#endif // BOURSE_H_INCLUDED
