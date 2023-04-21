#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED

using namespace std;

class Portefeuille {
    private :
        double solde;
        vector<Titre> Titres;
    public :
        void ajouterTitre (Titre );
        void retirerTitre (Titre );
        void deposerMontant (double );
        void retirarMontant (double );
};

void Portefeuille::ajouterTitre (Titre titre){
    Titres.push_back(titre);
}

void Portefeuille::retirerTitre (Titre titre){
    Titres.pop_back()
}
void Portefeuille::deposerMontant (double montant){
    solde+=montant;
}
void Portefeuille::retirarMontant (double montant){
    solde-=montant;
}


#endif // PORTEFEUILLE_H_INCLUDED
