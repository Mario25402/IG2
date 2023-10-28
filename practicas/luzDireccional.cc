#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class LuzDireccional : public Luz
{
public:
    LuzDireccional(Tupla2f direccion, int idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular);

};

#endif