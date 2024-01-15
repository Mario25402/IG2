// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************

class ObjRevolucion : public Malla3D
{
   public:
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool textura = false) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool textura = false) ;

    float centrar();

protected:
    std::vector<Tupla3f> perfil;

    void calcularTexturas();
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool textura = false);
} ;




#endif
