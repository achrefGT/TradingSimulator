#ifndef TITRE_H_INCLUDED
#define TITRE_H_INCLUDED

using namespace std;

class Titre {
    private :
        string nomAction;
        int quantite;
	public:
		Titre(string nomAction = "", int quantite = 0):nomAction(nomAction), quantite(quantite) {}
		string getNomAction() const;
		int getQuantite() const;

};
string Titre::getNomAction() const{
	return nomAction;
}

int Titre::getQuantite() const
{
	return quantite;
}

#endif // TITRE_H_INCLUDED
