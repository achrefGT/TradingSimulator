#ifndef PERSISTANCEPRIXJOURNALIER_H_INCLUDED
#define PERSISTANCEPRIXJOURNALIER_H_INCLUDED

using namespace std;

class PersistancePrixJournaliers
{
    public:
       static vector<PrixJournalier> lirePrixJournaliersDUnFichier(string chemin){
            vector<PrixJournalier> historique;
            ifstream f(chemin);
            int nbLignes= 0;
            string entete,sJour,sMois,sAnnee,sPrix,nom;
            if(f.is_open()){
                f>>entete;
                while(!f.eof()){
                    PrixJournalier pj;
                    f>>pj;
                    historique.push_back(pj);
                    nbLignes++;
                    if (nbLignes==9) break;
                }
            }
            return historique;
        }
};


#endif // PERSISTANCEPRIXJOURNALIER_H_INCLUDED
