#include <iostream>
#include "Ecosysteme.h"
using namespace std;

int main()
{
    Ecosysteme eco1;
    string nom_syst="Eco1";
    eco1.Charger_Fichier(nom_syst);
    eco1.Affichage_ecosyst();

    eco1.Evolution_Temporelle();

    eco1.Affichage_ecosyst();
}
