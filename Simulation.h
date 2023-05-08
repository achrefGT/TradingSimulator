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




double prixAction (vector<PrixJournalier> vect,string nomAction){
    double prix=0;
    for(const PrixJournalier& pj : vect){
        if (pj.getNomAction()==nomAction) {
            prix=pj.getPrix();
        }
    };
    return prix;
}


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
            {"NB_TRANSACTIONS", 0},
            {"NB_ACHATS", 0},
            {"NB_VENTES", 0},
            {"TEMPS_GET_ACTIONS_DISPO_AUJ_microsec", 0},
            {"TEMPS_SIMULATION_microsec", 0}
        };
        if (dateDebut>dateFin || budget<=0 || !(dateDebut.VerifDate() && dateFin.VerifDate())) return stats;
        Portefeuille portfeuil(budget);
        double prix;
        bourse.setDateAujourdHui(dateDebut);
        auto start = chrono::high_resolution_clock::now();
        auto actionsAujourdhui = bourse.getActionsDisponiblesParDate(dateFin);
        auto stop = chrono::high_resolution_clock::now();  
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        stats["TEMPS_GET_ACTIONS_DISPO_AUJ_microsec"]=duration.count();
        for (Date date = dateDebut; date <= dateFin; date.incrementerDate()){
            if (!bourse.getActionsDisponiblesParDate(date).empty()){
                cout<<"les transactions effectuees pendant la date : "<<date<<" solde : "<<portfeuil.getSolde()<<endl;
                for (int i=0;i<1+rand()%100;i++){
               // for (int i=0;i<3;i++){
                    Transaction transaction=trader.choisirTransaction(bourse,portfeuil);
                    if (transaction.getType() == rien || transaction.getTitre().getQuantite()==0 )  cout<<" -- "<<transaction<<endl;
                    else{
                        if (transaction.getType() == achat && transaction.getTitre().getQuantite()>0 && (prix=prixAction(bourse.getPrixJournaliersParDate(date),transaction.getTitre().getNomAction()))){
                            if  ( portfeuil.ajouterTitre(transaction.getTitre())){
                                if ((portfeuil.retirerMontant(transaction.getTitre().getQuantite()*prix))){    
                                    stats["NB_ACHATS"]++;
                                    cout<<" -> "<<transaction<<" "<<prix<<endl;
                                }
                            }
                                else cout << "ACHAT IMPOSSIBLE" << endl;

                        }
                        else if (transaction.getType() == vente && transaction.getTitre().getQuantite()>0 && (prix=prixAction(bourse.getHistorique(),transaction.getTitre().getNomAction()))){
                            if ( portfeuil.retirerTitre(transaction.getTitre())){
                                  if (portfeuil.deposerMontant(prix*transaction.getTitre().getQuantite()) ) {
                                    stats["NB_VENTES"]++;
                                    cout<<" <- "<<transaction<<" "<<prix<<endl;
                                  }                            
                            }
                            else cout << "VENTE IMPOSSIBLE" << endl;
                        }
                    }
                }
            }
            bourse.setDateAujourdHui(bourse.getDateAujourdHui().incrementerDate());
        }
        long valueTitres=0;
        for(Titre t : portfeuil.getTitres()){
            valueTitres+=t.getQuantite()*prixAction(bourse.getPrixJournaliersParDate(dateFin),t.getNomAction());
        };
        stats["NB_TRANSACTIONS"]=stats["NB_ACHATS"]+stats["NB_VENTES"];
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
