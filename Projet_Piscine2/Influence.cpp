#include "Influence.h"

using namespace std;

Influence::Influence()
{
   m_e1=0;
   m_e2=0;
   m_coefficient=0;

}

Influence::Influence(int e1, int e2, float coef)
{
    m_e1=e1;
    m_e2=e2;
    m_coefficient=coef;
}

Influence::~Influence()
{

}
