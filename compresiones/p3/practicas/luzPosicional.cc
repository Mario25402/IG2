#include "luzPosicional.h"

LuzPosicional::LuzPosicional(Tupla3f direccion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    // Rellenar variables de la superclase
    this->id = idLuz;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->posicion = Tupla4f(direccion[0], direccion[1], direccion[2], 1);
}