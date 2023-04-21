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
        virtual vector<string> getActionsDisponiblesParDate(Date date) const = 0;
        virtual vector<PrixJournalier> getPrixJournaliersParDate(Date date) const = 0;
};

Date Bourse::getDateFinRecherche() const{
    return dateFinRecherche;
}


class BourseVector : public Bourse {
    private:
        vector<PrixJournalier> historique;
    public:
        BourseVector(Date dFR,vector<PrixJournalier> vect) : Bourse(dFR),historique(vect) {};
        virtual vector<string> getActionsDisponiblesParDate(Date date) const;
        virtual vector<PrixJournalier> getPrixJournaliersParDate(Date date) const;
        vector<PrixJournalier> getHistorique() const;
};

vector<PrixJournalier> BourseVector::getHistorique() const {
    return historique;
    }


vector<string> BourseVector::getActionsDisponiblesParDate(Date date) const{
    vector<string> actionsDisponibles;
    for (const PrixJournalier& prix : historique) {
        if (prix.getDate() <= date) {
            actionsDisponibles.push_back(prix.getNomAction());
        }
    }
    return actionsDisponibles;
}

vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(Date date) const{
    vector<PrixJournalier> prixJournaliers;
    for (const PrixJournalier& prix : historique){
        if (prix.getDate() <= date) {
            prixJournaliers.push_back(prix);
        }
    }
    return prixJournaliers;
}


#endif // BOURSE_H_INCLUDED
