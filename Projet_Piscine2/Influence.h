#ifndef INFLUENCE_H_INCLUDED
#define INFLUENCE_H_INCLUDED
#include "Espece.h"

using namespace std;

class Influence
{

private:
    int m_e1;
    int m_e2;
    float m_coefficient;

public:
    Influence();
    ~Influence();
    Influence(int e1, int e2, float coef);
};



#endif // INFLUENCE_H_INCLUDED
