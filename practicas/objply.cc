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

   /*for (int i = 0; i < f.size(); i++){
      std::cout << "face #" << i << " readed: (" << f[i][0] << ", " << f[i][1] << ", " << f[i][2] << ")" << std::endl ;
   }*/
}


