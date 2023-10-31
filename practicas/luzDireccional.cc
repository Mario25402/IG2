#include "luzDireccional.h"
using namespace std;

LuzDireccional::LuzDireccional(Tupla2f direccion, int idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    // No tenemos mas de 8 luces
    assert (idLuz >= 1 and idLuz <= 8);

    // Rellenar variables de la superclase
    this->id = idLuz;
    alfa = direccion[0];
    beta = direccion[1];

    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    calcularPosicion(alfa, beta);
}

void LuzDireccional::setAnguloAlfa(int angulo){
    alfa = angulo;
    calcularPosicion(alfa, beta);
}

void LuzDireccional::setAnguloBeta(int angulo){
    beta = angulo;
    calcularPosicion(alfa, beta);
}

void LuzDireccional::calcularPosicion(int alfa, int beta){
    // Pasar las coordendas esfericas a coordenadas cartesianas
    float x = sin(alfa) * cos(beta);
    float y = sin(alfa) * sin(beta);
    float z = cos(alfa);

    this->posicion = Tupla4f(x*30, y*30, z*30, 0);
}