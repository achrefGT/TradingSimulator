#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED
#include "Titre.h"

using namespace std;

enum typeTransaction {vente,achat,rien};

class Transaction {
    private :
        Titre titre;
        typeTransaction type;
    public :
        Transaction(Titre titre=Titre(),typeTransaction type=rien) : titre(titre),type(type){};
        Titre getTitre()const{return titre;};
        typeTransaction getType()const{return type;};
        friend ostream& operator<< (ostream& flux , Transaction tx);
};
ostream& operator<< (ostream& flux ,Transaction tx){
    if (tx.type==rien) flux <<"rien";
    else if (tx.type==achat) flux <<"achat : "<<tx.titre;
    else if (tx.type==vente) flux <<"vente : "<<tx.titre;
    return flux;
}

#endif // TRANSACTION_H_INCLUDED
