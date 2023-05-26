#ifndef TITRE_H_INCLUDED
#define TITRE_H_INCLUDED

using namespace std;

class Titre {
    private :
        string nomAction;
        int quantite;
	public:
		Titre(string nomAction = "", int quantite = 0):nomAction(nomAction), quantite(quantite) {};
		~Titre(){};
		string getNomAction() const;
		int getQuantite() const;
		bool operator==(const Titre&) const;
        friend ostream& operator<< (ostream& flux , Titre t);
 //     friend istream& operator>> (istream& flux, Titre& t);
};
/*
istream& operator>> (istream& flux, Titre& t){
    string Qte;
    do {
        getline(flux,t.nomAction,':');
        getline(flux,Qte);
        t.quantite=stoi(Qte);
    }while(t.quantite<1);       // il faut que la quantite != 0
    return flux;
}
*/
ostream& operator<< (ostream& flux , Titre t ){
        flux << t.getNomAction() << " | Quantite : " << t.getQuantite() ;
        return flux;
    }

string Titre::getNomAction() const{
	return nomAction;
}

int Titre::getQuantite() const
{
	return quantite;
}

bool Titre::operator==(const Titre& titre) const{
    return (nomAction==titre.getNomAction());
}


#endif // TITRE_H_INCLUDED
