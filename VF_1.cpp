#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Date {
    private :
        int jour ;
        int mois ;
        int annee ;
    public :
        Date(int jj,int mm,int aa);
        int getJour() const;
        int getMois() const;
        int getAnnee() const;
        void incrementerDate();
        friend ostream& operator<< (ostream& flux , Date d);
        friend istream& operator>> (istream& flux, Date& d);
        bool VerifDate31(int j,int m) const;
        bool VerifDate30(int j,int m) const;
        bool Isleap(int a) const;
        bool operator==(const Date& d) const;
        bool operator<(const Date& d) const;
        bool operator>(const Date& d) const ;
         bool operator<=(const Date& d) const;
        bool VerifDate() const;
};
istream& operator>> (istream& flux,Date& d){
    string sJour,sMois,sAnnee;
    do {
        getline(flux,sJour,'/');
        getline(flux,sMois,'/');
        getline(flux,sAnnee);
        d.jour=stoi(sJour);
        d.mois=stoi(sMois);
        d.annee=stoi(sAnnee);
    }while(!(d.VerifDate()));
    return flux;
}

ostream& operator<< (ostream& flux , Date d ){
        flux << d.jour << "/" << d.mois << "/" << d.annee ;
        return flux;
    }
Date::Date (int jj,int mm,int aa){
    jour=jj;
    mois=mm;
    annee=aa;
}

int Date::getJour() const {
    return jour;
}

int Date::getMois() const {
    return mois;
}

int Date::getAnnee() const {
    return annee;
}



void Date::incrementerDate(){
    if ((mois==2 && ((Isleap(annee) && jour ==29) || (!Isleap(annee) && jour==28))) || (VerifDate30(jour,mois) && jour==30) || (VerifDate31(jour,mois) && jour==31)){
            jour=1;
            if (mois==12) {annee++;mois=1;}
            else mois++;
    }
    else jour++;


}

bool Date::Isleap(int a) const{
    if (a%4==0 || (a%100==0 && a%400==0)) {
        return true;
    }
    return false;
}

bool Date::VerifDate31(int j, int m) const{
    if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && j >= 1 && j <= 31) {
        return true;
    }
    return false;
}

bool Date::VerifDate30(int j, int m) const{
    if ((m == 4 || m == 6 || m == 9 || m == 11) && j >= 1 && j <= 30) {
        return true;
    }
    return false;
}
bool Date::VerifDate() const{
            if(jour>0 && jour<=31 && mois>0 && mois <13 && annee>0 )
                {return true;}
            return false;
        }
bool Date::operator==(const Date& d) const {
    return (jour == d.jour && mois == d.mois && annee == d.annee);
}

bool Date::operator<(const Date& d) const {
    if (annee < d.annee) {
        return true;
    }
    else if (annee > d.annee) {
        return false;
    }
    else {
        if (mois < d.mois) {
            return true;
        }
        else if (mois > d.mois) {
            return false;
        }
        else {
            if (jour < d.jour) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

bool Date::operator>(const Date& d) const {
    if (annee > d.annee) {
        return true;
    }
    else if (annee < d.annee) {
        return false;
    }
    else {
        if (mois > d.mois) {
            return true;
        }
        else if (mois < d.mois) {
            return false;
        }
        else {
            if (jour > d.jour) {
            return true;
            }
            else {
            return false;
            }
        }
    }
}


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


bool Date::operator<=(const Date& d) const {
    if (annee <= d.annee) {
        return true;
    }
    else if (annee > d.annee) {
        return false;
    }
    else {
        if (mois <= d.mois) {
            return true;
        }
        else if (mois > d.mois) {
            return false;
        }
        else {
            if (jour <= d.jour) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

class PersistancePrixJournaliers
{
    public:
       static vector<PrixJournalier> lirePrixJournaliersDUnFichier(string chemin){
            vector<PrixJournalier> historique;
            ifstream f(chemin);
            int nbLignes= 0;
            string entete,sJour,sMois,sAnnee,sPrix,nom;
            if(f.is_open()){
                f>>entete;
                while(!f.eof()){
                    PrixJournalier pj;
                    f>>pj;
                    historique.push_back(pj);
                    nbLignes++;
                    if (nbLignes==9) break;
                }
            }
            return historique;
        }
};


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
        vector<string> getActionsDisponiblesParDate(Date date) const;
        vector<PrixJournalier> getPrixJournaliersParDate(Date date) const;
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

int main(){

    Date d1(4, 9, 2023);
    Date d2(31, 12, 2022);
    Date d3(28, 2, 2021);
    Date d4(29, 2, 2020);
    Date d5(0,0,0);
    cout << "donner la Date (format: jour/mois/annee) -> " ;
    cin >> d5;
    cout << "Date 1: " << d1 <<"\nDate 2: "<<d2<<"\nDate 3: "<< d3 <<"\nDate 4: "<< d4 <<"\nDate 5: "<<d5<< endl;
    cout << "**************************************************\n";
    cout << "Date 1 is equal to Date 2: " << (d1 == d2) << endl;
    cout << "Date 1 is equal to Date 3: " << (d1 == d3) << endl;
    cout << "Date 1 is less than Date 2: " << (d1 < d2) << endl;
    cout << "Date 1 is less than Date 3: " << (d1 < d3) << endl;
    cout << "Date 1 is greater than Date 2: " << (d1 > d2) << endl;
    cout << "Date 1 is greater than Date 3: " << (d1 > d3) << endl;
    cout << "**************************************************\n";

    d1.incrementerDate();
    cout << "Date 1 after incrementing -> " << d1 << endl;
    d2.incrementerDate();
    cout << "Date 2 after incrementing -> " << d2 << endl;
    d3.incrementerDate();
    cout << "Date 3 after incrementing-> " << d3 << endl;
    d4.incrementerDate();
    cout << "Date 4 after incrementing -> " << d4 << endl;
    d5.incrementerDate();
    cout << "Date 5 after incrementing -> " << d5 << endl;

    cout << "**************************************************\n";
    PersistancePrixJournaliers ppj;
    Date dateFinRecherche(16, 4, 2022);
    BourseVector bourse(dateFinRecherche,ppj.lirePrixJournaliersDUnFichier("prices_simple.csv"));

    Date date(4, 1, 2010);
    vector<string> actionsDisponibles = bourse.getActionsDisponiblesParDate(date);
    cout << "Available stocks on : " << date << ":" <<endl;
    if (actionsDisponibles.size()==0) {
            cout << "  pas des actions pour cette date " << endl;
    }
    else {
        for (string action : actionsDisponibles) {
            cout << " - " << action << endl;
        }
    }

    date = Date(1, 1, 2023);
    vector<PrixJournalier> prixJournaliers = bourse.getPrixJournaliersParDate(date);
    cout << "PrixJournalier objects for " << date << ":" <<endl;
    if (prixJournaliers.size()==0) {
            cout << "  pas des prix journaliers pour cette date " << endl;
    }
    else {
        for (PrixJournalier prix : prixJournaliers) {
            cout << " - " << prix << endl;
        }
    }


    vector<PrixJournalier> historique = bourse.getHistorique();
    cout << " l'historique pour cette bourse :"<<endl;
    for (PrixJournalier prix : historique) {
        cout << "Date: " << prix.getDate() << " | Nom d'action: "  << prix.getNomAction() <<" | Prix: " << prix.getPrix() << endl;
    }
return 0;
}
