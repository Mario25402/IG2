#ifndef OBJPLY_H_INCLUDED
#define OBJPLY_H_INCLUDED

#include "auxiliar.h"
#include "ply_reader.h"
#include "malla.h"

 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************
class ObjPLY: public Malla3D {
public:
    ObjPLY( const std::string & nombre_archivo ) ;
    float centrar();
};

#endif


