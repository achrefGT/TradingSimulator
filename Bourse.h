#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
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
                actionsDisponibles.push_back(pj.getNomAction());    // pour une date donn�e, si il ya un prix max il ne faut pas le d�passer
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
                prixJournaliers.push_back(pj);            // pour une date donn�e, si il ya un prix max il ne faut pas le d�passer
            }
        }
    }
    return prixJournaliers;
}


//////////////////// BourseSet ////////////////
class BourseSet : public Bourse {
private:
    set<PrixJournalier> historique;

public:
    BourseSet(set<PrixJournalier>& h, Date dte) : historique(h), Bourse(dte) {}

    vector<string> getActionsDisponiblesParDate(Date d, double prixMax = 0.0) const  {
        vector<string> actions;
        auto it = historique.lower_bound(PrixJournalier(d, 0,""));
        while (!(it == historique.end()) && (it->getDate() == d)) {
            actions.push_back(it->getNomAction());
            it++;
        }
        return actions;
    }

    vector<PrixJournalier> getPrixJournaliersParDate(Date d, double prixMax = 0.0) const  {
        vector<PrixJournalier> Pj;
        auto it = historique.lower_bound(PrixJournalier(d, 0,""));
        while (!(it == historique.end()) && (it->getDate() == d) && (it->getPrix() <= prixMax)) {
            Pj.push_back(*it);
            it++;
        }
        return Pj;
    }
    vector<PrixJournalier> getHistorique() const {
    vector<PrixJournalier> hist;
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= dateAujourdHui) {
                hist.push_back(pj);
        }
    };
    return hist;        
    }

};
/*------------------------------------------------*/
// set map et multimap 

#endif // BOURSE_H_INCLUDED
























/*
    PrixJournalier pj(aujourd'hui,"",0);
it=monhistoriqueSet.lower_bound(pj);
while(!end && date=aujourd'hui){
    copie
    it++;
}
*/
