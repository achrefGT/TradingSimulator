#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

using namespace std;

class Simulation {
    private :
        Date dateDebut;
        Date dateFin;
        Date dateCourante;
        double solde;
    public :
         static void executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double solde);
         Date getDateDebut () const;
         Date getDateFin () const;
         Date getDateCourante () const;
         double getSolde () const;

};
Date Simulation::getDateDebut () const {return dateDebut;}
Date Simulation::getDateFin () const {return dateFin;}
Date Simulation::getDateCourante () const {return dateCourante;}
double Simulation::getSolde () const{ return solde;}
void Simulation::executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double solde){

}

#endif // SIMULATION_H_INCLUDED
