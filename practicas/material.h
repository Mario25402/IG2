#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "auxiliar.h"
#include "luz.h"

class Material
{
public:
    Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo);
    void aplicar();

private:
    float brillo;

    Tupla4f ambiente;
    Tupla4f difuso;
    Tupla4f especular;
};

#endif