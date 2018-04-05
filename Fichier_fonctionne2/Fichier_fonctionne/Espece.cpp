#include "Espece.h"
#include <string>

Espece::Espece()
{
    m_nom="";
    m_K=0;
    m_N=0;
    m_r=0;
}

Espece::~Espece()
{

}

Espece::Espece(string nom, int N, float r, int K)
{
    m_nom=nom;
    m_N=N;
    m_r=r;
    m_K=K;
}

string Espece:: getnom()
{
    return m_nom;
}

    int Espece:: getN()
    {
        return m_N;
    }
    float Espece :: getr()
    {
        return m_r;
    }
    int Espece :: getK ()
    {
        return m_K;
    }
