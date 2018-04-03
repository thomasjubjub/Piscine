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
