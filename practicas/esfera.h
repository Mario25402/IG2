// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************

class Esfera : public ObjRevolucion
{
private:
    float radio;

public:
    Esfera(int num_vert_perfil = 10, int num_instancias_perf = 20, float r = 1.0f);
    float getRadio();

};

#endif