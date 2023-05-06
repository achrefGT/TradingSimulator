#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "Date.h"
#include "PrixJournalier.h"
#include "PersistancePrixJournalier.h"

using namespace std;



class Bourse {
    protected:
        Date dateAujourdHui;
    public:
        Bourse(Date dateAujourdHui) : dateAujourdHui(dateAujourdHui) {};
        void setDateAujourdHui(Date date){if(date.VerifDate()) dateAujourdHui=date;};
        Date getDateAujourdHui() const {return dateAujourdHui;};
        virtual vector<string> getActionsDisponiblesParDate(Date,double prixMax = 0.0) const = 0;
        virtual vector<PrixJournalier> getPrixJournaliersParDate(Date,double prixMax = 0.0) const = 0;
        virtual vector<PrixJournalier> getHistorique() const = 0;
};


class BourseVector : public Bourse {
    private:
        vector<PrixJournalier> historique;
    public:
        BourseVector(Date da,vector<PrixJournalier> vect) : Bourse(da),historique(vect) {};
        vector<string> getActionsDisponiblesParDate(Date,double) const;
        vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
        vector<PrixJournalier> getHistorique() const;
};

vector<PrixJournalier> BourseVector::getHistorique() const {
    vector<PrixJournalier> hist;
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= dateAujourdHui) {
                hist.push_back(pj);
        }
    };
    return hist;
    }


vector<string> BourseVector::getActionsDisponiblesParDate(Date date,double prixMax=0.0) const{
    vector<string> actionsDisponibles;
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() == date) {
            if ((prixMax && pj.getPrix()<=prixMax) || !prixMax){
                actionsDisponibles.push_back(pj.getNomAction());    // pour une date donnée, si il ya un prix max il ne faut pas le dépasser
            }
        }
    }
    return actionsDisponibles;
}

vector<PrixJournalier> BourseVector::getPrixJournaliersParDate(Date date,double prixMax=0.0) const{
    vector<PrixJournalier> prixJournaliers;
    for (const PrixJournalier& pj : historique){
        if (pj.getDate() == date) {
            if ((prixMax && pj.getPrix() <=prixMax) || !prixMax){
                prixJournaliers.push_back(pj);            // pour une date donnée, si il ya un prix max il ne faut pas le dépasser
            }
        }
    }
    return prixJournaliers;
}


#endif // BOURSE_H_INCLUDED

