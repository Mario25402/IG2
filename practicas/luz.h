#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "auxiliar.h"
#include "GL/gl.h"

class Luz
{
public:
    void activar();
    void desactivar();
    
protected:
    Tupla4f posicion;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

    GLenum id;

    void setColores(Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular);
    void setPosicion(Tupla4f posicion);
};

#endif
