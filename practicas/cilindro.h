// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cilindro.h

//
// #############################################################################

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

// *****************************************************************************

class Cilindro : public ObjRevolucion
{
private:
    float altura;
    float radio;
    
public:
    Cilindro(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 1.0f, float r = 1.0f);

};

#endif
