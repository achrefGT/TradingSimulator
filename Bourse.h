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
        double prixAction(const vector<PrixJournalier>&,const string&) const;
        virtual vector<string> getActionsDisponiblesParDate(Date,double prixMax = 0.0) const = 0;
        virtual vector<PrixJournalier> getPrixJournaliersParDate(Date,double prixMax = 0.0) const = 0;
        virtual vector<PrixJournalier> getHistorique() const = 0;
        virtual map<string,vector<double>> getPrixActionParMois (string nomAction="",int mois=0) const = 0;

};

double Bourse::prixAction (const vector<PrixJournalier>& vect,const string& nomAction) const {
    double prix=0;
    for(const PrixJournalier& pj : vect){
        if (pj.getNomAction()==nomAction) {
            prix=pj.getPrix();
        }
    };
    return prix;
}

///////////////////////////////// Bourse Vecteur /////////////////////////////////////////////

class BourseVector : public Bourse {
    private:
        vector<PrixJournalier> historique;
    public:
        BourseVector(Date da,vector<PrixJournalier> vect) : Bourse(da),historique(vect) {};
        vector<string> getActionsDisponiblesParDate(Date,double) const;
        vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
        vector<PrixJournalier> getHistorique() const;
        map<string,vector<double>> getPrixActionParMois (string,int) const;

};

map<string,vector<double>> BourseVector::getPrixActionParMois (string nomAction="",int mois=0) const{
    map<string,vector<double>> resultat;
    mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 1 ) : mois;
    vector<PrixJournalier> hist = this->getHistorique();
    for (const PrixJournalier& pj : hist){
        if(pj.getDate().getMois()==mois && dateAujourdHui.getAnnee()==pj.getDate().getAnnee()){
            if(nomAction == "" || nomAction==pj.getNomAction()){
                resultat[pj.getNomAction()].push_back(pj.getPrix());
            }
        }
    }
    return resultat;
}

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

///////////////////////////////// Bourse Multimap /////////////////////////////////////////////

class BourseMultimap : public Bourse {
private :
    multimap<Date,PrixJournalier> historique;
public :
    BourseMultimap(Date date,multimap<Date,PrixJournalier> mmap) : Bourse(date),historique(mmap) {};
    vector<string> getActionsDisponiblesParDate(Date,double) const;
    vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
    vector<PrixJournalier> getHistorique() const;
    map<string,vector<double>> getPrixActionParMois (string,int) const;

};

vector<string> BourseMultimap::getActionsDisponiblesParDate(Date date, double prixMax = 0.0) const {
    vector<string> actionsDisponibles;

    auto range = historique.equal_range(date);

    for (auto it = range.first; it != range.second; ++it) {
        const PrixJournalier& pj = it->second;

        if ((prixMax && pj.getPrix() <= prixMax) || !prixMax) {
            actionsDisponibles.push_back(pj.getNomAction());
        }
    }

    return actionsDisponibles;
}




vector<PrixJournalier> BourseMultimap::getPrixJournaliersParDate(Date date, double prixMax = 0.0) const {
    vector<PrixJournalier> prixJournaliers;

    auto range = historique.equal_range(date);

    for (auto it = range.first; it != range.second; ++it) {
        const PrixJournalier& pj = it->second;

        if ((prixMax && pj.getPrix() <= prixMax) || !prixMax) {
            prixJournaliers.push_back(pj);
        }
    }

    return prixJournaliers;
}


vector<PrixJournalier> BourseMultimap::getHistorique() const {
    vector<PrixJournalier> hist;
    for (const auto& pair : historique) {
        const PrixJournalier& pj = pair.second;
        if (pj.getDate() <= dateAujourdHui) {
            hist.push_back(pj);
        }
    }
    return hist;
}

map<string,vector<double>> BourseMultimap::getPrixActionParMois (string nomAction="",int mois=0) const{
    map<string,vector<double>> resultat;
    int annee = dateAujourdHui.getAnnee();
    mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 1 ) : mois;
    Date dateDebut(1,mois,dateAujourdHui.getAnnee());
    Date dateFin = dateDebut.isLeap() ? Date (29,mois,annee) : (dateDebut.verifDate30() ? Date(30,mois,annee) : (dateDebut.verifDate31() ? Date(31,mois,annee) : Date(28,mois,annee)));

    auto lower = historique.lower_bound(dateDebut);
    while (lower!=historique.end() && lower->first <= dateFin){
        const PrixJournalier& pj = lower->second;
        if(nomAction == "" || nomAction==pj.getNomAction()){
                resultat[pj.getNomAction()].push_back(pj.getPrix());
            }
        ++lower;
    }


    return resultat;
}

//////////////////// BourseSet ////////////////

class BourseSet : public Bourse {
private:
    set<PrixJournalier> historique;

public:
    BourseSet(Date dte,set<PrixJournalier>& h) : Bourse(dte), historique(h) {}

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

    map<string,vector<double>> getPrixActionParMois (string nomAction="",int mois=0) const{
        map<string,vector<double>> resultat;
        mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 1 ) : mois;
        vector<PrixJournalier> hist = this->getHistorique();
        for (const PrixJournalier& pj : hist){
            if(pj.getDate().getMois()==mois && dateAujourdHui.getAnnee()==pj.getDate().getAnnee()){
                if(nomAction == "" || nomAction==pj.getNomAction()){
                    resultat[pj.getNomAction()].push_back(pj.getPrix());
                }
            }
        }
        return resultat;
}
};

#endif // BOURSE_H_INCLUDED

