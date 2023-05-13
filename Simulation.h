#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include "Trader.h"
#include "PrixJournalier.h"
#include "Portefeuille.h"
#include "Transaction.h"
#include <random>
#include <chrono>
#include <map>



using namespace std;

class Simulation {
private:
    Date dateDebutSimulation;
    Date dateFinSimulation;
    Date dateCourante;
    double Budget;
public:
    Simulation(Date debut, Date fin, double budget=0) : dateDebutSimulation(debut),dateFinSimulation(fin),dateCourante(debut),Budget(budget){};
    static map<string, long> executer(Bourse& bourse,Trader& trader,Date dateDebut,Date dateFin,double budget) {
        auto startSimulation = chrono::high_resolution_clock::now();
        map<string, long> stats = {
            {"NB_TX", 0},
            {"NB_ACHATS", 0},
            {"NB_VENTES", 0},
            {"TEMPS_GET_ACTIONS_DISPO_AUJ_microsec", 0},
            {"NBRE_GET_ACTIONS_DISPO_AUJ", 0},
            {"NBRE_GET_PRIX_ACTION_DATE", 0},
            {"TEMPS_GET_PRIX_ACTION_AUJ_microsec", 0},
            {"TEMPS_SIMULATION_microsec", 0},
            {"TEMPS_TX_microsec", 0},

        };
        if (dateDebut>dateFin || budget<=0 || !(dateDebut.VerifDate() && dateFin.VerifDate())) return stats;
        Portefeuille portfeuil(budget);
        double prix;
        bourse.setDateAujourdHui(dateDebut);
        for (Date date = dateDebut; date <= dateFin; date.incrementerDate()){
            auto start = chrono::high_resolution_clock::now();
            auto actionsAujourdhui = bourse.getActionsDisponiblesParDate(date);
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            stats["TEMPS_GET_ACTIONS_DISPO_AUJ_microsec"]+=duration.count();
            ++stats["NBRE_GET_ACTIONS_DISPO_AUJ"];
            if (!actionsAujourdhui.empty()){
               // cout<<"les transactions effectuees pendant la date : "<<date<<" solde : "<<portfeuil.getSolde()<<endl;
               // for (int i=0;i<1+rand()%100;i++){
                for (int i=0;i<100;i++){
                    auto startTX = chrono::high_resolution_clock::now();
                    Transaction transaction=trader.choisirTransaction(bourse,portfeuil);
                    auto stopTX = chrono::high_resolution_clock::now();
                    auto durationTX = chrono::duration_cast<chrono::microseconds>(stopTX - startTX);
                    if (transaction.getType() == rien || transaction.getTitre().getQuantite()==0 ) ;// cout<<" -- rien"<<endl;
                    else{
                        auto startPrix = chrono::high_resolution_clock::now();
                        prix = bourse.prixAction(bourse.getHistorique(),transaction.getTitre().getNomAction());
                        auto stopPrix = chrono::high_resolution_clock::now();
                        auto durationPrix = chrono::duration_cast<chrono::microseconds>(stopPrix - startPrix);
                        stats["TEMPS_GET_PRIX_ACTION_AUJ_microsec"]+=durationPrix.count();
                        ++stats["NBRE_GET_PRIX_ACTION_DATE"];
                        if (prix){
                            if (transaction.getType() == achat && transaction.getTitre().getQuantite()>0){
                                    if  ( portfeuil.ajouterTitre(transaction.getTitre())){
                                        if ((portfeuil.retirerMontant(transaction.getTitre().getQuantite()*prix))){
                                            ++stats["NB_ACHATS"];
                                            stats["TEMPS_TX_microsec"]+=durationTX.count();
                                          //  cout<<" -> "<<transaction<<" "<<prix<<endl;
                                        }
                                    }
                                    else cout << "ACHAT IMPOSSIBLE" << endl;

                            }
                            else if (transaction.getType() == vente && transaction.getTitre().getQuantite()>0){
                                if ( portfeuil.retirerTitre(transaction.getTitre())){
                                      if (portfeuil.deposerMontant(prix*transaction.getTitre().getQuantite()) ) {
                                        ++stats["NB_VENTES"];
                                        stats["TEMPS_TX_microsec"]+=durationTX.count();
                                      //  cout<<" <- "<<transaction<<" "<<prix<<endl;
                                      }
                                }
                                else cout << "VENTE IMPOSSIBLE" << endl;
                            }
                        }
                    }
                }
            }
            bourse.setDateAujourdHui(bourse.getDateAujourdHui().incrementerDate());
        }
        long valueTitres=0;
        for(Titre t : portfeuil.getTitres()){
            valueTitres+=t.getQuantite()*bourse.prixAction(bourse.getPrixJournaliersParDate(dateFin),t.getNomAction());
        };
        stats["NB_TX"]=stats["NB_ACHATS"]+stats["NB_VENTES"];
        stats["VALEUR_TITRES"] = valueTitres+portfeuil.getSolde();
        auto stopSimulation = chrono::high_resolution_clock::now();
        auto durationSimulation = chrono::duration_cast<chrono::microseconds>(stopSimulation - startSimulation);
        stats["TEMPS_SIMULATION_microsec"]+=durationSimulation.count();
        return stats;
    };
    Date getDateDebut () const {return dateDebutSimulation;};
    Date getDateFin () const {return dateFinSimulation;};
    Date getDateCourante () const {return dateCourante;};
    double getSolde () const{return Budget;};
};



#endif // SIMULATION_H_INCLUDED
