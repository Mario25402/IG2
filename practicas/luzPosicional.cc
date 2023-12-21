#include "luzPosicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    // Rellenar variables de la superclase
    this->id = idLuz;
    this->angulo  = 0;

    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->posicion = Tupla4f(posicion[0], posicion[1], posicion[2], 1);
}

void LuzPosicional::animarPosicion(){
    angulo += 0.01;
    angulo = fmod(angulo, 360);

    float x = (50 * cos(angulo)) + 50;
    float z = (50 * sin(angulo)) + 50;

    this->posicion[0] = x;
    this->posicion[2] = z;

    setPosicion(this->posicion);
}