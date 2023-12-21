#include "luzDireccional.h"
#include "GL/gl.h"
using namespace std;

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    this->id = idLuz;
    alfa = direccion[0];
    beta = direccion[1];

    setColores(colorAmbiente, colorDifuso, colorEspecular);
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
    float x = sin(beta) * cos(alfa);
    float y = sin(beta) * sin(alfa);
    float z = cos(beta);

    float modulo = sqrt(x*x + y*y + z*z);
    x /= modulo;
    y /= modulo;
    z /= modulo;

    this->posicion = Tupla4f(x, y, z, 0); // Ajustar al tamaño de los objetos
    setPosicion(this->posicion);

}

void LuzDireccional::animarColores(){
    if (colorDifuso[0] < 1.0)
        colorDifuso[0] += 0.01;
    else if (colorDifuso[1] < 1.0)
        colorDifuso[1] += 0.01;
    else if (colorDifuso[2] < 1.0)
        colorDifuso[2] += 0.01;

    // Volver a valores iniciales
    if (colorDifuso[0] >= 1.0 and colorDifuso[1] >= 1.0 and colorDifuso[2] >= 1.0){
        colorDifuso[0] = 0.4;
        colorDifuso[1] = 0.4;
        colorDifuso[2] = 0.4;
    }

    setColores(colorAmbiente, colorDifuso, colorEspecular);
}