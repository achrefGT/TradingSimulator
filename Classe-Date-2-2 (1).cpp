#include <iostream>
#include <cstdlib>

using namespace std;

class date {
    private :
        int jour ;
        int mois ;
        int annee ;
    public :
        date(int jj,int mm,int aa);
        int getJour() const;
        int getMois() const;
        int getAnnee() const;
        void incrementerDate();
        friend ostream& operator<< (ostream& flux , date d);
        bool VerifDate31(int j,int m) const;
        bool VerifDate30(int j,int m) const;
        bool Isleap(int a) const;
        bool operator==(const date& d) const;
        bool operator<(const date& d) const;
        bool operator>(const date& d) const ;
};

ostream& operator<< (ostream& flux , date d ){
        flux<<"jour : "<< d.jour << "\nmois : " << d.mois << "\nannee : " << d.annee << endl;
        return flux;
    }

date::date (int jj,int mm,int aa){
    jour=jj;
    mois=mm;
    annee=aa;
}

int date::getJour() const {
    return jour;
}

int date::getMois() const {
    return mois;
}

int date::getAnnee() const {
    return annee;
}

void date::incrementerDate(){
    if ((mois==2 && ((Isleap(annee) && jour ==29) || (!Isleap(annee) && jour==28))) || (VerifDate30(jour,mois) && jour==30) || (VerifDate31(jour,mois) && jour==31)){
            jour=1;
            if (mois==12) {annee++;mois=1;}
            else mois++;
    }
    else jour++;


}


/*
void date::incrementJour(){
    if ((VerifDateFB(jour,mois) && ((Isleap(jour,mois) && jour ==29) || (!Isleap(jour,mois) && jour==28))) || (VerifDate30(jour,mois) && jour==30) || (VerifDate31(jour,mois) && jour==31)) jour=1;
    else jour++ ;
}

void date::incrementMois(){
    if (mois==12) mois=1;
    mois++;
}

void date::incrementAnnee() {
    annee++;
}
*/
bool date::Isleap(int a) const{
    if (a%4==0 || (a%100==0 && a%400==0)) {
        return true;
    }
    return false;
}

bool date::VerifDate31(int j, int m) const{
    if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && j >= 1 && j <= 31) {
        return true;
    }
    return false;
}

bool date::VerifDate30(int j, int m) const{
    if ((m == 4 || m == 6 || m == 9 || m == 11) && j >= 1 && j <= 30) {
        return true;
    }
    return false;
}


bool date::operator==(const date& d) const {
    return (jour == d.jour && mois == d.mois && annee == d.annee);
}

bool date::operator<(const date& d) const {
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

bool date::operator>(const date& d) const {
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

// main function to test the date class
int main() {
date d1(4, 9, 2023);
date d2(31, 12, 2022);
date d3(28, 2, 2021);
date d4(29, 2, 2020);
cout << "Date 1: " << d1 << endl;
cout << "Date 2: " << d2 << endl;
cout << "Date 3: " << d3 << endl;
cout << "Date 4: " << d4 << endl;

cout << "Date 1 is equal to Date 2: " << (d1 == d2) << endl;
cout << "Date 1 is equal to Date 3: " << (d1 == d3) << endl;
cout << "Date 1 is less than Date 2: " << (d1 < d2) << endl;
cout << "Date 1 is less than Date 3: " << (d1 < d3) << endl;
cout << "Date 1 is greater than Date 2: " << (d1 > d2) << endl;
cout << "Date 1 is greater than Date 3: " << (d1 > d3) << endl;

d1.incrementerDate();
cout << "Date 1 after incrementing : " << d1 << endl;

d2.incrementerDate();
cout << "Date 2 after incrementing: " << d2 << endl;

d3.incrementerDate();
cout << "Date 3 after incrementing: " << d3 << endl;

d4.incrementerDate();
cout << "Date 4 after incrementing: " << d4 << endl;

return 0;
}


