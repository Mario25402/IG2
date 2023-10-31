#include "luzPosicional.h"

LuzPosicional::LuzPosicional(Tupla2f direccion, int idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    // No tenemos mas de 8 luces
    assert (idLuz >= 1 and idLuz <= 8);

    // Rellenar variables de la superclase
    this->id = idLuz;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->posicion = Tupla4f(direccion[0], direccion[1], -50, 1);
}