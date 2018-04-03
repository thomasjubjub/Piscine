#ifndef ESPECE_H_INCLUDED
#define ESPECE_H_INCLUDED
#include <string>
using namespace std;

class Espece
{
    friend class Influence;
private:
    string m_nom;
    int m_K; //nombre maximum
    int m_N; //nombre actuel
    float m_r; //rythme de croissance

public:
    Espece();
    ~Espece();
    Espece(string nom, int N, float r, int K);
};



#endif // ESPECE_H_INCLUDED
