#include "Ecosysteme.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Ecosysteme::Ecosysteme()
{

}

Ecosysteme::~Ecosysteme()
{

}
int Ecosysteme::get_nombre_espece()
{
    return m_nombre_espece;
}
void Ecosysteme::Charger_Fichier(string nom_fichier)
{
    string extension = nom_fichier + ".txt";

    int e1, e2, n, K;
    float r, coef;
    string nom;
    ifstream fichier(extension.c_str(), ios::in);


    if(fichier)
    {


        fichier >> m_nombre_espece;

        for(int i=0; i<m_nombre_espece; i++)
        {
            fichier >> nom >> n >> r >> K;
            vecEspece.push_back(new Espece(nom, n, r, K));

        }


        fichier >> m_nombre_influence;

        for(int i=0; i<m_nombre_influence; i++)
        {

            fichier >> e1 >> e2 >> coef;
            vecInfluence.push_back(new Influence(e1, e2, coef));
        }

    }

}
