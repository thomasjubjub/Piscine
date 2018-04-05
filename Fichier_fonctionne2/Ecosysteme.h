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
};



#endif // ECOSYSTEME_H_INCLUDED
