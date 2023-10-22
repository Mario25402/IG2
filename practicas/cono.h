// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cono.h

//
// #############################################################################

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************

class Cono : public ObjRevolucion
{
private:
    float altura;
    float radio;

public:
    Cono(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 1.0f, float r = 1.0f);

};

#endif
