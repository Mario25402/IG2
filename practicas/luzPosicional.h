#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class LuzPosicional : public Luz
{
public:
    LuzPosicional(Tupla3f direccion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular);
    
    void setPosicion(Tupla3f direccion);
};

#endif