#ifndef BOURSE_H_INCLUDED
#define BOURSE_H_INCLUDED
#include "Date.h"
#include "PrixJournalier.h"
#include "PersistancePrixJournalier.h"

using namespace std;



class Bourse {
    protected:
        Date dateAujourdHui;
        vector<PrixJournalier> historique;
    public:
        Bourse(Date dateAujourdHui,vector<PrixJournalier> historique) : dateAujourdHui(dateAujourdHui),historique(historique) {};
        Date getDateAujourdHui() const {return dateAujourdHui;};
        double prixAction(const vector<PrixJournalier>&,const string&) const;
        virtual void setDateAujourdHui(Date date) = 0;
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
        vector<PrixJournalier> historiqueVector;
    public:
        BourseVector(Date date,vector<PrixJournalier> historique);
        vector<string> getActionsDisponiblesParDate(Date,double) const;
        vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
        vector<PrixJournalier> getHistorique() const { return historiqueVector;};
        map<string,vector<double>> getPrixActionParMois (string,int) const;
        void setDateAujourdHui(Date date);

};


BourseVector::BourseVector(Date date,vector<PrixJournalier> historique) : Bourse(date,historique) {
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= dateAujourdHui) {
                historiqueVector.push_back(pj);
        }
    };
}

void BourseVector::setDateAujourdHui(Date date) {
    if (date.VerifDate()) {
        dateAujourdHui = date;
        historiqueVector.clear();

        for (const PrixJournalier& pj : historique) {
            if (pj.getDate() <= dateAujourdHui) {
                historiqueVector.push_back(pj);
            }
        }
    }
}



map<string,vector<double>> BourseVector::getPrixActionParMois (string nomAction="",int mois=0) const{
    map<string,vector<double>> resultat;
    mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 12 ) : mois;
    for (const PrixJournalier& pj : historiqueVector){
        if(pj.getDate().getMois()==mois && ((dateAujourdHui.getAnnee()==pj.getDate().getAnnee() && mois!=12) || (dateAujourdHui.getAnnee()-1==pj.getDate().getAnnee() && mois==12))){
            if(nomAction == "" || nomAction==pj.getNomAction()){
                resultat[pj.getNomAction()].push_back(pj.getPrix());
            }
        }
    }
    return resultat;
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
    multimap<Date,PrixJournalier> historiqueMultimap;
public :
    BourseMultimap(Date date,vector<PrixJournalier> historique);
    vector<string> getActionsDisponiblesParDate(Date,double) const;
    vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
    map<string,vector<double>> getPrixActionParMois (string,int) const;
    void setDateAujourdHui(Date date);
    vector<PrixJournalier> getHistorique() const ;


};

vector<PrixJournalier> BourseMultimap::getHistorique() const{
    vector<PrixJournalier> resultat;
    for (const auto& pair : historiqueMultimap){
        resultat.push_back(pair.second);
    }
    return resultat;
}

BourseMultimap::BourseMultimap(Date date, vector<PrixJournalier> historique) : Bourse(date, historique) {
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= dateAujourdHui) {
            historiqueMultimap.emplace(pj.getDate(), pj);
        }
    }
}


void BourseMultimap::setDateAujourdHui(Date date) {
    if (date.VerifDate()) {
        dateAujourdHui = date;
        historiqueMultimap.clear();

        for (const PrixJournalier& pj : historique) {
            if (pj.getDate() <= dateAujourdHui) {
                historiqueMultimap.insert(make_pair(pj.getDate(),pj));
            }
        }
    }
}

vector<string> BourseMultimap::getActionsDisponiblesParDate(Date date, double prixMax = 0.0) const {
    vector<string> actionsDisponibles;

    auto range = historiqueMultimap.equal_range(date);

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

    auto range = historiqueMultimap.equal_range(date);

    for (auto it = range.first; it != range.second; ++it) {
        const PrixJournalier& pj = it->second;

        if ((prixMax && pj.getPrix() <= prixMax) || !prixMax) {
            prixJournaliers.push_back(pj);
        }
    }

    return prixJournaliers;
}

map<string,vector<double>> BourseMultimap::getPrixActionParMois (string nomAction="",int mois=0) const{
    map<string,vector<double>> resultat;

    mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 12 ) : mois;
    int annee = mois==12 ? dateAujourdHui.getAnnee()-1 : dateAujourdHui.getAnnee();
    Date dateDebut(1,mois,dateAujourdHui.getAnnee());
    Date dateFin = dateDebut.isLeap() ? Date (29,mois,annee) : (dateDebut.verifDate30() ? Date(30,mois,annee) : (dateDebut.verifDate31() ? Date(31,mois,annee) : Date(28,mois,annee)));

    auto lower = historiqueMultimap.lower_bound(dateDebut);
    while (lower!=historiqueMultimap.end() && lower->first <= dateFin){
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
    set<PrixJournalier> historiqueSet;

public:
    BourseSet(Date date, vector<PrixJournalier> historique) : Bourse(date, historique) {
        for (const PrixJournalier& pj : historique) {
            if (pj.getDate() <= dateAujourdHui) {
                historiqueSet.emplace(pj);
            }
        }
    }


    void setDateAujourdHui(Date date) {
        if (date.VerifDate()) {
            dateAujourdHui = date;
            historiqueSet.clear();

            for (const PrixJournalier& pj : historique) {
                if (pj.getDate() <= dateAujourdHui) {
                     historiqueSet.insert(pj);
                }
            }
        }
    }


    vector<string> getActionsDisponiblesParDate(Date d, double prixMax = 0.0) const {
        vector<string> actions;
        auto it = historiqueSet.lower_bound(PrixJournalier(d, 0, ""));
        while (it != historiqueSet.end() && it->getDate() == d) {
            if (it->getDate() == d &&((prixMax && it->getPrix() <= prixMax) || !prixMax)){actions.push_back(it->getNomAction());}
            ++it;
        }
        return actions;
    }


    vector<PrixJournalier> getPrixJournaliersParDate(Date d, double prixMax = 0.0) const  {
        vector<PrixJournalier> prixJournaliers;

        auto it = historiqueSet.lower_bound(PrixJournalier(d, 0, ""));
        while (it != historiqueSet.end() && it->getDate() == d) {
            if (it->getDate() == d &&((prixMax && it->getPrix() <= prixMax) || !prixMax)){prixJournaliers.push_back(*it);}
            ++it;
        }
        return prixJournaliers;

    }

    vector<PrixJournalier> getHistorique() const {
        return vector<PrixJournalier>(historiqueSet.begin(), historiqueSet.end());
    }

    map<string,vector<double>> getPrixActionParMois (string nomAction="",int mois=0) const{

        map<string,vector<double>> resultat;
        mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 12 ) : mois;
        int annee = mois==12 ? dateAujourdHui.getAnnee()-1 : dateAujourdHui.getAnnee();
        Date dateDebut(1,mois,dateAujourdHui.getAnnee());
        Date dateFin = dateDebut.isLeap() ? Date (29,mois,annee) : (dateDebut.verifDate30() ? Date(30,mois,annee) : (dateDebut.verifDate31() ? Date(31,mois,annee) : Date(28,mois,annee)));
        auto lower = historiqueSet.lower_bound(PrixJournalier(dateDebut,0,""));
        while (lower!=historiqueSet.end() && lower->getDate() <= dateFin){
            const PrixJournalier& pj = *lower;
            if(nomAction == "" || nomAction==pj.getNomAction()){
                    resultat[pj.getNomAction()].push_back(pj.getPrix());
                }
            ++lower;
        }
        return resultat;
    }


};

///////////////////////////////// Bourse Map /////////////////////////////////////////////

class BourseMap : public Bourse {
private :
    map<Date,vector<PrixJournalier>> historiqueMap;
public :
    BourseMap(Date date,vector<PrixJournalier> historique);
    vector<string> getActionsDisponiblesParDate(Date,double) const;
    vector<PrixJournalier> getPrixJournaliersParDate(Date,double) const;
    map<string,vector<double>> getPrixActionParMois (string,int) const;
    void setDateAujourdHui(Date date);
    vector<PrixJournalier> getHistorique() const ;


};

vector<PrixJournalier> BourseMap::getHistorique() const{
    vector<PrixJournalier> resultat;
    for (const auto& pair : historiqueMap){
        for (const auto& pj : pair.second){
            resultat.push_back(pj);
        }
    }
    return resultat;
}

BourseMap::BourseMap(Date date, vector<PrixJournalier> historique) : Bourse(date, historique) {
    for (const PrixJournalier& pj : historique) {
        if (pj.getDate() <= dateAujourdHui) {
            historiqueMap[pj.getDate()].push_back(pj);
        }
    }
}


void BourseMap::setDateAujourdHui(Date date) {
    if (date.VerifDate()) {
        dateAujourdHui = date;
        historiqueMap.clear();

        for (const PrixJournalier& pj : historique) {
            if (pj.getDate() <= dateAujourdHui) {
                historiqueMap[pj.getDate()].push_back(pj);
            }
        }
    }
}

vector<string> BourseMap::getActionsDisponiblesParDate(Date date, double prixMax) const {
    vector<string> actionsDisponibles;

    auto it = historiqueMap.find(date);
    if (it != historiqueMap.end()) {
        for (const PrixJournalier& pj : it->second) {
            if (prixMax == 0.0 || pj.getPrix() <= prixMax) {
                actionsDisponibles.push_back(pj.getNomAction());
            }
        }
    }
    return actionsDisponibles;
}


vector<PrixJournalier> BourseMap::getPrixJournaliersParDate(Date date, double prixMax) const {
    vector<PrixJournalier> prixJournaliers;

    auto it = historiqueMap.find(date);
    if (it != historiqueMap.end()) {
        const vector<PrixJournalier>& prixJournalierVector = it->second;
        for (const PrixJournalier& pj : prixJournalierVector) {
            if (prixMax == 0.0 || pj.getPrix() <= prixMax) {
                prixJournaliers.push_back(pj);
            }
        }
    }
    return prixJournaliers;
}


map<string,vector<double>> BourseMap::getPrixActionParMois (string nomAction="",int mois=0) const{
    map<string,vector<double>> resultat;

    mois = (!mois || mois>=13 || mois<=0) ? (dateAujourdHui.getMois()!=1 ? dateAujourdHui.getMois()-1 : 12 ) : mois;
    int annee = mois==12 ? dateAujourdHui.getAnnee()-1 : dateAujourdHui.getAnnee();
    Date dateDebut(1,mois,dateAujourdHui.getAnnee());
    Date dateFin = dateDebut.isLeap() ? Date (29,mois,annee) : (dateDebut.verifDate30() ? Date(30,mois,annee) : (dateDebut.verifDate31() ? Date(31,mois,annee) : Date(28,mois,annee)));

    auto lower = historiqueMap.lower_bound(dateDebut);
    while (lower!=historiqueMap.end() && lower->first <= dateFin){
        for (const PrixJournalier& pj : lower->second){
            if(nomAction == "" || nomAction==pj.getNomAction()){
                resultat[pj.getNomAction()].push_back(pj.getPrix());
            }
        }
        ++lower;
    }


    return resultat;
}

#endif // BOURSE_H_INCLUDED

