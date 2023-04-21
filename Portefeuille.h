#ifndef PORTEFEUILLE_H_INCLUDED
#define PORTEFEUILLE_H_INCLUDED
#include"Titre.h"

using namespace std;

class Portfeuille {
    private :
        double solde;
        vector<Titre> titres;
    public :
        Portfeuille(double solde = 0.0):solde(solde) {};
		double getSolde() const;
		vector<Titre> getTitres() const;
//		bool chercherTitre (const Titre titre) const;
		bool ajouterTitre(const Titre titre);
		bool retirerTitre(const Titre titre);
        bool deposerMontant (double );
        bool retirerMontant (double );
};
/*
bool chercherTitre (const Titre titre) const{
    bool test = true;
    for(Titre t : Titres){
        if (t.getNomAction()==titre.getNomAction()) test=false;
    }
    return test;
};*/

bool Portfeuille::ajouterTitre (const Titre titre){
    for (int i=0; i<titres.size(); i++){
		if (titres[i].getNomAction() == titre.getNomAction()){
            titres.push_back(Titre(titre.getNomAction(),titre.getQuantite()+titres[i].getQuantite()));
			titres.erase(titres.begin() + i);
			return true;
		}
    }
	titres.push_back(titre);
    return true;
}

bool Portfeuille::retirerTitre (const Titre titre){
    double difference;
    for (int i=0; i<titres.size(); i++){
		if (titres[i].getNomAction() == titre.getNomAction() && titres[i].getQuantite() >= titre.getQuantite()){
            difference=titres[i].getQuantite()-titre.getQuantite();
            if (difference>0) titres.push_back(Titre(titre.getNomAction(),difference));
			titres.erase(titres.begin() + i);
			return true;
		}
    }
    return true;
}
bool Portfeuille::deposerMontant (double montant){
    solde+=montant;
    return true;
}
bool Portfeuille::retirerMontant (double montant){
    if (solde >= montant){
		solde -= montant;
		return true;
	}
	return false;
}




#endif // PORTFEUILLE_H_INCLUDED
