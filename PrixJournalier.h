#ifndef PRIXJOURNALIER_H_INCLUDED
#define PRIXJOURNALIER_H_INCLUDED

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


};


ostream& operator<< (ostream& flux , PrixJournalier pj){
  //flux<<"date : "<< pj.date << "\nprix : " << pj.prix << "\nnom de l'action : " << pj.nomAction << endl;
    flux << pj.date << ";" << pj.nomAction << ";" << pj.prix << endl;
    return flux;
}

istream& operator>> (istream& flux, PrixJournalier& pj){
    string sPrix,nom;
    Date d(0,0,0);
    flux>>d;
    getline(flux,nom,';');
    getline(flux,nom,';');
    getline(flux,sPrix);
    pj.date=d;
    pj.prix=stod(sPrix);
    pj.nomAction=nom;
    return flux;
}


#endif // PRIXJOURNALIER_H_INCLUDED
