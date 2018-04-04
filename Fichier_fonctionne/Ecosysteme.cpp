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
        do
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
        while (fichier.good());
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
}

void Ecosysteme:: Evolution_Temporelle()
{
    int taille;
    //vector<Influence*>::iterator it;
    taille=vecEspece.size()-1;
    int quotient=0;
    int e1;
    ///a tout modifier sommet* vecit->e1
    vecEspece[taille]->m_N=(vecEspece[taille]->m_N)*(vecEspece[taille]->m_r);

//    for(it=vecInfluence.begin(); it!=vecInfluence.end(); it++)
//    {
//        if(it->m_e2==taille && taille>=0)
//        {
//            vecEspece[it->m_e1]->m_K=(it->coef)*(vecInfluence[taille]->m_N);
//
//            quotient=(vecEspece[it->m_e1]->m_N)/(vecEspece[it->m_e1]->m_K);
//
//            vecEspece[it->m_e1]->m_N=(vecEspece[it->m_e1]->m_N)+(vecEspece[it->m_e1]->m_N)*(vecEspece[it->m_e1]->m_r)(1-quotient);
//            taille--;
//        }
//    }
cout<<"je suis avant le for"<<endl;
    for(int i=vecInfluence.size()-1; i>=0; i--)
    {
        cout<<"je suis la avant le if"<<endl;
        do{
        if(vecInfluence[i]->m_e2==taille)
        {
            e1=vecInfluence[i]->m_e1;
             vecEspece[e1]->m_K=(vecInfluence[i]->m_coefficient)*(vecEspece[taille]->m_N);

            quotient=(vecEspece[e1]->m_N)/(vecEspece[e1]->m_K);

            vecEspece[e1]->m_N=(vecEspece[e1]->m_N)+(vecEspece[e1]->m_N)*(vecEspece[e1]->m_r)*(1-quotient);

        }
        taille--;
        }while(taille>=0);
    }




}



