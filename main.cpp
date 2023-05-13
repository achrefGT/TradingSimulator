#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <map>
#include <tuple>
#include <set>
#include <algorithm>
#include "Bourse.h"
#include "Date.h"
#include "PrixJournalier.h"
#include "PersistancePrixJournalier.h"
#include "Portefeuille.h"
#include "Simulation.h"
#include "Titre.h"
#include "Transaction.h"
#include "Trader.h"
#include "Test.h"


using namespace std;


int main(){
    srand(time(NULL));
    cout<<"-------------------- Testes pour la class Date ---------------------------------\n"<<endl;
    Date d(0,0,0);
    Date d1(4, 9, 2023);
    Date d11(5,9,2023);
    Date d2(31, 12, 2022);
    Date d21(1,1,2023);
    Date d3(28, 2, 2021);
    Date d31(1,3,2021);
    Date d4(29, 2, 2020);
    Date d41(1,3,2020);
    Date d5(4,9,2023);
    Date d6(-1,-1,-1);
    Test<int>::runTest(d1.getJour(),4,"Test constructeur et getJour de la class Date");
    Test<int>::runTest(d1.getMois(),9,"Test constructeur et getMois de la class Date");
    Test<int>::runTest(d1.getAnnee(),2023,"Test constructeur et getAnnee de la class Date");
    Test<Date>::runTest(d1,d5,"Test operateur == de la class Date");
    Test<bool>::runTest(d2==d5,false,"Test operateur == de la class Date");
    Test<bool>::runTest(d1<=d5,true,"Test operateur <= de la class Date");
    Test<bool>::runTest(d3<=d2,true,"Test operateur <= de la class Date");
    Test<bool>::runTest(d2<=d3,false,"Test operateur <= de la class Date");
    Test<bool>::runTest(d2<d3,false,"Test operateur < de la class Date");
    Test<bool>::runTest(d3<d2,true,"Test operateur < de la class Date");
    Test<bool>::runTest(d1>d2,true,"Test operateur > de la class Date");
    Test<bool>::runTest(d2>d1,false,"Test operateur > de la class Date");
    Test<Date>::runTest(d1.incrementerDate(),d11,"Test incrementerDate de la class Date");
    Test<bool>::runTest(d1.incrementerDate()==d21,false,"Test incrementerDate de la class Date");
    Test<Date>::runTest(d2.incrementerDate(),d21,"Test incrementerDate de la class Date");
    Test<Date>::runTest(d3.incrementerDate(),d31,"Test incrementerDate de la class Date");
    Test<Date>::runTest(d4.incrementerDate(),d41,"Test incrementerDate de la class Date");
    Test<bool>::runTest(d4.isLeap(),true,"Test operateur isLeap de la class Date");
    Test<bool>::runTest(d3.isLeap(),false,"Test operateur isLeap de la class Date");
    Test<bool>::runTest(d1.verifDate30(),true,"Test verifDate30 de la class Date");
    Test<bool>::runTest(d2.verifDate30(),false,"Test verifDate30 de la class Date");
    Test<bool>::runTest(d1.verifDate31(),false,"Test verifDate31 de la class Date");
    Test<bool>::runTest(d2.verifDate31(),true,"Test verifDate31 de la class Date");
    Test<bool>::runTest(d1.VerifDate(),true,"Test verifDate de la class Date");
    Test<bool>::runTest(d6.VerifDate(),false,"Test verifDate de la class Date");
    stringstream ss;
    ss << d6;
    ss << "\n" <<d2;
    ss >> d;
    Test<Date>::runTest(d2,d, "Test operator>> et operator<< de la class Date");
    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    vector<PrixJournalier> historique = PersistancePrixJournaliers::lirePrixJournaliersDUnFichier("prices_simple.csv");
    Bourse *bourse = new BourseMap(d1,historique);

    Date date(8, 1, 2010);
    date = Date(4, 1, 2010);

    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    cout<<endl<<"-------------------- Testes pour la class PrixJournalier ---------------------------------"<<endl<<endl;
    PrixJournalier pj1;
    Test<Date>::runTest(pj1.getDate(),Date(0,0,0),"Test constructeur par defaut et getDate de la class PrixJournalier");
    Test<string>::runTest(pj1.getNomAction(),"","Test constructeur par defaut et getNomAction de la class PrixJournalier");
    Test<double>::runTest(pj1.getPrix(),0.0,"Test constructeur par defaut et getPrix de la class PrixJournalier");
    PrixJournalier pj2(date,100,"google");
    Test<Date>::runTest(pj2.getDate(),date,"Test constructeur et getDate de la class PrixJournalier");
    Test<string>::runTest(pj2.getNomAction(),"google","Test constructeur et getNomAction de la class PrixJournalier");
    Test<double>::runTest(pj2.getPrix(),100,"Test constructeur et getPrix de la class PrixJournalier");
    stringstream ss1;
    ss1 << pj2;
    PrixJournalier pj3;
    ss1 >> pj3;
    Test<Date>::runTest(pj2.getDate(), pj3.getDate(), "Test operator>> et operator<< et getDate de la class PrixJournalier");
    Test<double>::runTest(pj2.getPrix(), pj3.getPrix(), "Test operator>> et operator<< et getPrix de la class PrixJournalier");
    Test<string>::runTest(pj2.getNomAction(), pj3.getNomAction(), "Test operator>> et operator<< et getNomAction de la class PrixJournalier");
    Test<bool>::runTest(pj1<pj2,true,"Test operator < de la class PrixJournalier");
    PrixJournalier pj4(date,50,"google");
    Test<bool>::runTest(pj4<pj2,true,"Test operator < de la class PrixJournalier");
    PrixJournalier pj5(date,50,"zzz");
    Test<bool>::runTest(pj4<pj5,true,"Test operator < de la class PrixJournalier");


    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    cout<<endl<<"-------------------- Testes pour la class Titre ---------------------------------"<<endl<<endl;
    Titre titre;
    Test<string>::runTest(titre.getNomAction(),"","Test constructeur par defaut et getNomAction de la class Titre");
    Test<int>::runTest(titre.getQuantite(),0,"Test constructeur par defaut et getQuantite de la class Titre");
    Titre titre1("APPLE",20);
    Test<string>::runTest(titre1.getNomAction(),"APPLE","Test constructeur et getNomAction de la class Titre");
    Test<int>::runTest(titre1.getQuantite(),20,"Test constructeur et getQuantite de la class Titre");
    Titre titre2("APPLE",50);
    Test<Titre>::runTest(titre1,titre2,"Test operateur == de la class Titre");
    Test<bool>::runTest(titre==titre1,false,"Test operateur == de la class Titre");


    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    cout<<endl<<"-------------------- Testes pour la class Portfeuille ---------------------------------"<<endl<<endl;
    Portefeuille pf;
    Test<long>::runTest(pf.getSolde(),0.0,"Test constructeur par defaut et getSolde de la class Portfeuille");
    Portefeuille pf1(100);
    Test<long>::runTest(pf1.getSolde(),100.0,"Test constructeur et getSolde de la class Portfeuille");
    pf.deposerMontant(100);
    Test<long>::runTest(pf.getSolde(),100.0,"Test deposerMontant de la class Portfeuille");
    pf.deposerMontant(-100);
    Test<long>::runTest(pf.getSolde(),100.0,"Test deposerMontant de la class Portfeuille");
    pf1.retirerMontant(50);
    Test<long>::runTest(pf1.getSolde(),50.0,"Test retirerMontant de la class Portfeuille");
    pf1.retirerMontant(-80);
    Test<long>::runTest(pf1.getSolde(),50.0,"Test retirerMontantt de la class Portfeuille");
    pf1.retirerMontant(80);
    Test<long>::runTest(pf1.getSolde(),50.0,"Test retirerMontant de la class Portfeuille");
    pf.ajouterTitre(titre1);
    Test<Titre>::runTest(titre1,pf.getTitres()[0],"Test ajouterTitre et getTitres de la class Portfeuille");
    Test<bool>::runTest(pf.retirerTitre(titre1),true,"Test retirerTitre de la class Portfeuille");
    Test<bool>::runTest(pf.ajouterTitre(titre),false,"Test ajouterTitre de la class Portfeuille");
    pf1.ajouterTitre(titre1);
    pf1.ajouterTitre(titre1);
    Test<long>::runTest(pf1.getTitres()[0].getQuantite(),40,"Test ajouterTitre de la class Portfeuille");
    Test<bool>::runTest(pf1.retirerTitre(titre),false,"Test retirerTitre de la class Portfeuille");
    Test<bool>::runTest(pf1.retirerTitre(titre2),false,"Test retirerTitre de la class Portfeuille");
    pf1.retirerTitre(titre1);
    Test<long>::runTest(pf1.getTitres()[0].getQuantite(),20,"Test retirerTitre de la class Portfeuille");
    Test<bool>::runTest(pf1.chercherTitre("APPLE"),true,"Test chercherTitre de la class Portfeuille");
    Test<bool>::runTest(pf1.chercherTitre("APPL"),false,"Test chercherTitre de la class Portfeuille");
    Test<int>::runTest(pf1.getQuantiteTitre("APPLE"),20,"Test getQuantiteTitre de la class Portfeuille");
    Test<bool>::runTest(pf1.getQuantiteTitre("APPLE")==2,false,"Test getQuantiteTitre de la class Portfeuille");



    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    cout<<endl<<"-------------------- Testes pour la class Transaction ---------------------------------"<<endl<<endl;
    Transaction tx;
    Test<Titre>::runTest(tx.getTitre(),Titre(),"Test constructeur par defaut et getTitre de la class Transaction");
    Test<typeTransaction>::runTest(tx.getType(),rien,"Test constructeur par defaut et getType de la class Transaction");
    Transaction tx1(titre1,achat);
    Test<Titre>::runTest(tx1.getTitre(),titre1,"Test constructeur de la Transaction");
    Test<typeTransaction>::runTest(tx1.getType(),achat,"Test constructeur de la class Transaction");

    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    cout<<endl<<"-------------------- Testes pour la class Bourse ---------------------------------"<<endl<<endl;
    Test<Date>::runTest(bourse->getDateAujourdHui(),d1,"Test getDateAujourdHui et constructeur de la calss Bourse");
    Date dateAujourdHui(4, 2, 2010);
    bourse->setDateAujourdHui(d6);
    Test<Date>::runTest(bourse->getDateAujourdHui(),d1,"Test setDateAujourdHui de la calss Bourse");
    bourse->setDateAujourdHui(dateAujourdHui);
    Test<Date>::runTest(bourse->getDateAujourdHui(),dateAujourdHui,"Test setDateAujourdHui de la calss Bourse");

    /* ---------------------------------------------------------------------------------------------------------------------------------------*/

    Trader* trader = new TraderMoyenne();

   // cout<<(trader->choisirTransaction(*bourse,pf1));


    Date d7(4,1,2010);
    Date d8(3,2,2010);

    cout<<endl<<"**********************"<<endl<<endl;
    auto stats = Simulation::executer(*bourse,*trader,d7,d8,1000);
    for(auto it:stats){cout<<it.first<<"\t"<<it.second<<endl; }


    return 0;
}
