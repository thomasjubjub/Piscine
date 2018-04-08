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

void Ecosysteme::Charger_Fichier(string nom_fichier)
{
    string extension = nom_fichier + ".txt";

    int e1, e2, n, K;
    float r,coef;
    string nom;
    string lala;
    ifstream fichier(extension.c_str(), ios::in);

    if(fichier)
    {
        do{
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

        }while (fichier.good());
    }

}

void Ecosysteme :: Affichage_ecosyst()
{
   for (int i = 0; i<vecEspece.size (); i++)
    {
        cout << vecEspece [i]->m_nom << "  " << vecEspece [i]->m_N << "  " <<vecEspece [i]->m_r << "  " << vecEspece [i]->m_K << endl;
     }

     for (int i=0; i< vecInfluence.size(); i++)
     {
        cout << vecInfluence [i]->m_e1 << "  " << vecInfluence [i]->m_e2 << "  et le coef " << vecInfluence [i]->m_coefficient << endl;
        }

        cout << endl;
        cout << endl;

}






