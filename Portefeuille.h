#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED
#include "Titre.h"

using namespace std;

class Portefeuille {
    private :
        double solde;
        vector<Titre> titres;
    public :
        Portefeuille(double solde = 0.0):solde(solde), titres() {};
		~Portefeuille(){};
		double getSolde() const;
        vector<Titre> getTitres() const;
		bool chercherTitre (const string) const;
		bool ajouterTitre(const Titre& titre);
		bool retirerTitre(const Titre& titre);
        bool deposerMontant (double );
        bool retirerMontant (double );
        int getQuantiteTitre (const string) const;
};

bool Portefeuille::chercherTitre (const string nomTitre) const{
    bool test = false;
    for(Titre t : titres){
        if (t.getNomAction()==nomTitre) test=true;
    }
    return test;
};

bool Portefeuille::ajouterTitre (const Titre& titre){
    if (titre.getQuantite()==0) return false;
    for (vector<Titre>::size_type i = 0; i<titres.size(); i++){
		if (titres[i] == titre){                                                                                  // si l'action existe déjà
            titres.push_back(Titre(titre.getNomAction(),titre.getQuantite() + titres[i].getQuantite()));          // on ajoute une avec la nouvelle quantité
			titres.erase(titres.begin() + i);                                                                     // puis on supprime la première
			return true;
		}
    }
	titres.push_back(titre);
    return true;
}

bool Portefeuille::retirerTitre(const Titre& titre) {
    double difference;
    for (vector<Titre>::size_type i = 0; i < titres.size(); i++) {
        if (titres[i] == titre && titres[i].getQuantite() >= titre.getQuantite()) {
            difference = titres[i].getQuantite() - titre.getQuantite();
            if (difference > 0) {                                                                                   // si l'action existe déjà et la quantite à retirer est < à la quantite existant
                titres.push_back(Titre(titre.getNomAction(), difference));                                          // on diminue la quantité et on ajoute une avec la nouvelle quantité
            }                                                                                                       // si l'action existe déjà et la quantite à retirer est = à la quantite existant on n'ajoute rien
            titres.erase(titres.begin() + i);                                                                       // puis on supprime la première
            return true;
        }
    }
    return false;
}


bool Portefeuille::deposerMontant (double montant){
    if(montant<0) return false;
    solde+=montant;
    return true;
}
bool Portefeuille::retirerMontant (double montant){
    if(montant<0) return false;
    if (solde >= montant){
		solde -= montant;
		return true;
	}
	return false;
}

double Portefeuille::getSolde() const{
    return solde;
}


vector<Titre> Portefeuille::getTitres() const {
    return titres;
}

int Portefeuille::getQuantiteTitre(const string nomTitre) const{
    for (Titre t : titres){
        if (t.getNomAction()==nomTitre) return t.getQuantite();
    }
    return 0;
}



#endif // PORTEFEUILLE_H_INCLUDED
