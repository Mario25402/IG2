#include "luzDireccional.h"
#include "GL/gl.h"
using namespace std;

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuz, Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
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
    float x = sin(beta) * cos(alfa);
    float y = sin(beta) * sin(alfa);
    float z = cos(beta);

    float modulo = sqrt(x*x + y*y + z*z);
    x /= modulo;
    y /= modulo;
    z /= modulo;

    this->posicion = Tupla4f(x, y, z, 0); // Ajustar al tamaño de los objetos
    glLightfv(id, GL_POSITION, posicion);

}