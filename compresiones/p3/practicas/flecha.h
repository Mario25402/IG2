#ifndef _FLECHA_H
#define _FLECHA_H

#include "objrevolucion.h"

// SE ACTIVA EN LA ESCENA EN EL MODO OBJETOS CON LA TECLA 'F'

class Flecha3D : public ObjRevolucion
{
    public:
    Flecha3D(float hPunta = 1.0f, float hAstil=1.0f, float nRrev=30);
};

#endif