#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class LuzPosicional : public Luz
{
private:
    float angulo;
    
public:
    LuzPosicional(Tupla3f posicion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular);
    
    void animarPosicion();
};

#endif