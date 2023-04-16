#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

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
        bool VerifDate() const;
};
istream& operator>> (istream& flux,Date& d){
    char separator;
    do {
        cout << "Merci de saisir un date valid (jj/mm/aa)"<<endl;
        flux >> d.jour >> separator >> d.mois >> separator >> d.annee;
        system("CLS");
    } while(!(d.VerifDate()));
    return flux;
}
ostream& operator<< (ostream& flux , Date d ){
        flux<<"jour : "<< d.jour << "\nmois : " << d.mois << "\nannee : " << d.annee << endl;
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
    flux<<"date : "<< pj.date << "\nprix : " << pj.prix << "\nnom de l'action : " << pj.nomAction << endl;
    return flux;
}

istream& operator>> (istream& flux, PrixJournalier& pj){
    string sJour,sMois,sAnnee,sPrix,nom;
    getline(flux,sJour,'/');
    getline(flux,sMois,'/');
    getline(flux,sAnnee,';');
    Date d(stoi(sJour),stoi(sMois),stoi(sAnnee));
    getline(flux,nom,';');
    getline(flux,sPrix);
    pj.date=d;
    pj.prix=stod(sPrix);
    pj.nomAction=nom;
    return flux;
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
                }
            }
            return historique;
        }
};


int main(){
    ifstream f("price.csv");
    int nbLignes= 0;
    string entete;
    Date d2(0,0,0);
    cin >> d2;
    cout << d2;
    Date d(14,12,2001);
    PrixJournalier pj(d,15,"google");
    f>>entete;
    f>>pj;
    cout<<pj;
    return 0;
}
