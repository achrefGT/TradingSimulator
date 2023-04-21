#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED

using namespace std;

enum typeTransaction {vente,achat,rien};

class Transaction {
    private :
        string nomAction;
        int quantite;
        typeTransaction type;
    public :
        Transaction(string nom="",int qte=0,typeTransaction type=rien) : nomAction(nom),quantite(qte),type(type){};
        string getNomAction()const{return nomAction;};
        int getQuantite()const{return quantite;};
        typeTransaction getType()const{return type;};
};


#endif // TRANSACTION_H_INCLUDED
