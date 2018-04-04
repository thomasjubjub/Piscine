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
    cout << endl;
    cout << endl;
}

void Ecosysteme:: Evolution_Temporelle()
{
    int taille;
    taille=vecEspece.size()-1;
    int quotient=0;
    int e1, e2;
    int predecesseurs=0, successeurs=0;
    vector<Influence*>::iterator it;


    ///on calcul le N du premier en partant du bas
    vecEspece[taille]->m_N=(vecEspece[taille]->m_N)*(vecEspece[taille]->m_r);
    cout << vecEspece[taille]->m_K << endl;
    cout << vecEspece[taille]->m_N << endl;



    for(int i=vecEspece.size()-1; i>-1; i--)
    {



        ///on compte le nombre de predecesseurs

        predecesseurs = 0;

        for (it = vecInfluence.begin(); it!=  vecInfluence.end(); it ++)
        {

            if (i==(*it)->m_e1)
            {

                predecesseurs = predecesseurs+1;

            }
        }


        cout << vecEspece [i]->m_nom << "  a : " <<predecesseurs << "pred" << endl;

        ///on calcule K pour toutes les espèces à partir du rang 2


        if(predecesseurs==1)
        {
            vecEspece[i]->m_K=0;
            for (it = vecInfluence.begin(); it!=  vecInfluence.end(); it ++)
            {
                if ((*it)->m_e1 == i)
                {
                    vecEspece[i]->m_K=((*it)->m_coefficient)*(vecEspece[(*it)->m_e2]->m_N);
                }
            }
        }
        else if(predecesseurs>1)
        {
            vecEspece[i]->m_K=0;
            for(it=vecInfluence.begin(); it!=vecInfluence.end(); it++)
            {
                if((*it)->m_e1==i)
                {
                    vecEspece[i]->m_K=(vecEspece[i]->m_K)+(((*it)->m_coefficient)*(vecEspece[(*it)->m_e2]->m_N));
                }

            }
        }

        cout << vecEspece[i]->m_K << endl ;
    }

    ///on calcule N


    for(int i=0; i<vecEspece.size(); i++)
    {
        for (it = vecInfluence.begin(); it!=  vecInfluence.end(); it ++)
        {
            if((*it)->m_e1==i)
            {
                successeurs=successeurs+1;
            }
        }

    }

    if(successeurs==1)
    {
        for (it = vecInfluence.begin(); it!=  vecInfluence.end(); it ++)
        {
            if((*it)->m_e1==i)
            {
                vecEspece[i]->m_N=((vecEspece[i]->m_N)+((vecEspece[i]->m_N)*(vecEspece[i]->m_r)*(1-((vecEspece[i]->m_N)/(vecEspece[i]->m_K))))-((*it)->m_coefficient*vecEspece[(*it)->m_e2]->m_N);
            }
        }

    }
    else if (successeurs<1)
    {

    }

    //vecEspece[i]->m_N = vecEspece

//        cout<<"la valeur de i est "<<i<<endl;

//
//        vecEspece[e1]->m_K=0;

//            if(it->)
//
//

//            ///on calcul le K de e1 en fonction du nombre de predecesseurs
//            for(int c=0; c<predecesseurs; c++)
//            {
//                vecEspece[e1]->m_K=(vecEspece[e1]->m_K)+(((vecInfluence[i]->m_coefficient))*(vecEspece[e2]->m_N));
//            }
//            ///on calcul le N de e1
//            quotient=(vecEspece[e1]->m_N)/(vecEspece[e1]->m_K);
//            vecEspece[e1]->m_N=(vecEspece[e1]->m_N)+(vecEspece[e1]->m_N*vecEspece[e1]->m_r)*(1-quotient);


}




//

//j=i--;
//        cout<<"je suis la avant le if"<<endl;
//        do
//        {
//            ///Si il bouffe 2 mecs ou pas
//            if(vecInfluence[i]->m_e2==taille || vecInfluence[i]->m_e2==doublons)
//            {
//                e1=vecInfluence[i]->m_e1;
//
//                if((vecInfluence[i]->m_e1)==(vecInfluence[j]->m_e1))
//                {
//                    vecEspece[e1]->m_K=((vecInfluence[i]->m_coefficient)*(vecEspece[taille]->m_N))+((vecInfluence[j]->m_coefficient)*(vecEspece[taille--]->m_N));
//                }
//                else
//                {
//                    vecEspece[e1]->m_K=(vecInfluence[i]->m_coefficient)*(vecEspece[taille]->m_N);
//
//                }
//                quotient=(vecEspece[e1]->m_N)/(vecEspece[e1]->m_K);
//                vecEspece[e1]->m_N=(vecEspece[e1]->m_N)+(vecEspece[e1]->m_N)*(vecEspece[e1]->m_r)*(1-quotient);
//
//                cout<<"apres le premier if"<<endl;
//
//                ///Si il se fait bouffer par 2
////
//                if((vecInfluence[i]->m_e2)==(vecInfluence[j]->m_e2))
//                {
//                     e2=vecInfluence[i]->m_e2;
//
//                     cout<<"dans le deuxieme if"<<endl;
//                    vecEspece[e2]->m_N=(vecEspece[e2]->m_N)+((vecEspece[e2]->m_N)*(vecEspece[e2]->m_r)*(1-quotient));
//
//                    cout<<"fin de calcul du n"<<endl;
//
//                    vecEspece[e2]->m_N=(vecEspece[e2]->m_N)-((vecInfluence[i]->m_coefficient*vecEspece[j]->m_N)+(vecInfluence[j]->m_coefficient*vecEspece[j--]->m_N));
//                    cout<<"avant le deuxieme else"<<endl;
//
//                }
//                else
//                {
//                    cout<<"dans le else du deuxieme if"<<endl;
//                    vecEspece[e2]->m_N=(vecEspece[e2]->m_N)+(vecEspece[e2]->m_N)*(vecEspece[e2]->m_r)*(1-quotient);
//                }




//        }
//        while(taille>=0);









