#ifndef ECOSYSTEME_H_INCLUDED
#define ECOSYSTEME_H_INCLUDED
#include "Influence.h"
#include <vector>
using namespace std;

class Ecosysteme
{
    friend class Espece;
    friend class Influence;
private:
    vector<Influence*> vecInfluence;
    vector<Espece*>vecEspece;
    int m_nombre_espece;
    int m_nombre_influence;

public:
    Ecosysteme();
    ~Ecosysteme();

    //methodes

    void Charger_Fichier(string nom_fichier);
    void Affichage_ecosyst();
    void Evolution_Temporelle();
    void Supprimer_Espece ();
    void Ajouter_Espece ();
    ///Faire Sauvegarde Fichier
    ///Penser à mettre un numéro pour connaitre l'ordre de réécriture ?
    /// Evolution dans le temps (à voir avec les temps de pauses
};



#endif // ECOSYSTEME_H_INCLUDED
