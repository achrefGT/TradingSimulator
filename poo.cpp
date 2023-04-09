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
        int getJour();
        int getMois();
        int getAnnee();
        friend ostream& operator<< (ostream& flux , date d);
};
ostream& operator<< (ostream& flux , date d ){
        flux<<"jour : "<< d.jour << "\n mois : " << d.mois << "\n annee : " << d.annee << endl;
        return flux;
    }
date::date (int jj,int mm,int aa){
    jour=jj;
    mois=mm;
    annee=aa;
}



int main (){
    date d(7,8,2001);
    cout << d;
    return 0;
}