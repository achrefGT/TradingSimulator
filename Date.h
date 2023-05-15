#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

using namespace std;

class Date {
    private :
        int jour ;
        int mois ;
        int annee ;
    public :
        Date(int jj,int mm,int aa);
        ~Date(){};
        int getJour() const;
        int getMois() const;
        int getAnnee() const;
        Date incrementerDate();
        friend ostream& operator<< (ostream& flux , Date d);
        friend istream& operator>> (istream& flux, Date& d);
        bool verifDate31() const;
        bool verifDate30() const;
        bool isLeap() const;
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
    }while(!(d.VerifDate() || flux.eof()));
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



Date Date::incrementerDate(){
    if (!this->VerifDate()) return *this;
    if ((mois==2 && ((this->isLeap() && jour ==29) || (!this->isLeap() && jour==28))) || ((this->verifDate30()) && jour==30) || ((this->verifDate31()) && jour==31)){
            jour=1;
            if (mois==12) {annee++;mois=1;}
            else mois++;
    }
    else jour++;
    return *this;

}

bool Date::isLeap() const{
    if (!this->VerifDate()) return false;
    if (annee%4==0 || (annee%100==0 && annee%400==0)) {
        return true;
    }
    return false;
}

bool Date::verifDate31() const{
    if (!this->VerifDate()) return false;
    if ((mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12) && jour >= 1 && jour <= 31) {
        return true;
    }
    return false;
}

bool Date::verifDate30() const{
    if (!this->VerifDate()) return false;
    if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour >= 1 && jour <= 30) {
        return true;
    }
    return false;
}
bool Date::VerifDate() const{
    if(jour>0 && jour<=31 && mois>0 && mois <13 && annee>=0 )
        {return true;}
    return false;
}
bool Date::operator==(const Date& d) const {
    if (!(this->VerifDate() || d.VerifDate())) return false;
    return (jour == d.jour && mois == d.mois && annee == d.annee);
}

bool Date::operator<(const Date& d) const {
    if (!(this->VerifDate() || d.VerifDate())) return false;
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
    if (!(this->VerifDate() || d.VerifDate())) return false;
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
bool Date::operator<=(const Date& d) const {
    if (!(this->VerifDate() || d.VerifDate())) return false;
    return (*this < d) || (*this == d);
}


#endif // DATE_H_INCLUDED