#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED
#include "Date.h"

using namespace std;


class PrixJournalier{
    private:
        Date date;
        double prix;
        string nomAction;
    public:
        PrixJournalier(Date d,float p,string n) : date(d),prix(p),nomAction(n){};
        PrixJournalier() : date(Date(0,0,0)), prix(0.0), nomAction("") {}
        friend ostream& operator<< (ostream& flux , PrixJournalier pj);
        friend istream& operator>> (istream& flux, PrixJournalier& pj);
        string getNomAction() const { return nomAction; };
        Date getDate() const { return date; };
        double getPrix() const { return prix; };
        bool operator<(const PrixJournalier& ) const;

};


ostream& operator<< (ostream& flux , PrixJournalier pj){
    flux << pj.date << ";" << pj.nomAction << ";" << pj.prix << endl;
    return flux;
}

istream& operator>> (istream& flux, PrixJournalier& pj){
    string sDate,sPrix,nom;
    getline(flux,sDate,';');
    getline(flux,pj.nomAction,';');
    getline(flux,sPrix);
    stringstream ss;
    ss << sDate;
    ss >> pj.date;
    pj.prix=stod(sPrix);
    return flux;
}

bool PrixJournalier::operator<(const PrixJournalier& other) const{

    return this->getDate() < other.getDate() ? true : (this->getPrix() < other.getPrix() ? true : (this->getNomAction() < other.getNomAction() ? true : false));

    /*bool resultat = this->getDate() < other.getDate();
    if(this->getDate()other.getDate()){
        resultat = this->getPrix() < other.getPrix();
    }
    return resultat;*/
}

#endif // PRIXJOURNALIER_H_INCLUDED
