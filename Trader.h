#ifndef TRADER_H_INCLUDED
#define TRADER_H_INCLUDED
#include "Transaction.h"
#include "Portefeuille.h"

using namespace std;

class Trader {
    public :
        virtual Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);

};

class TraderAleatoire : public Trader {
    public :
        Transaction choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille);

} ;

Transaction TraderAleatoire::choisirTransaction(const Bourse& bourse, const Portefeuille &portefeuille){

}


#endif // TRADER_H_INCLUDED
