#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   c.resize(v.size());
}

float ObjPLY::centrar()
{
   float min = INFINITY;

   for (int i = 0; i < v.size(); i++){
      if (v[i][1] < min)
         min = v[i][1];   
   }

   return min;
}