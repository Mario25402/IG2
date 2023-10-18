// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: piramidepentagonal.h

//
// #############################################################################

#ifndef PIRAMIDE_PENTAGONAL_H_INCLUDED
#define PIRAMIDE_PENTAGONAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Pirámide de base pentagonal con base centrada en el origen 

class PiramidePentagonal: public Malla3D
{
   public:
      PiramidePentagonal(float h=1.0,float r=0.5);

} ;




#endif
