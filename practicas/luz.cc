#include "luz.h"

void Luz::activar()
{
    if (glIsEnabled(id) == GL_FALSE){
        // Crear la luz
        setColores(colorAmbiente, colorDifuso, colorEspecular);
        setPosicion(posicion);

        // Activar la luz
        glEnable(id);
    }
}

void Luz::desactivar()
{
    if (glIsEnabled(id) == GL_TRUE)
        glDisable(id);

}

void Luz::setColores(Tupla4f colorAmbiente, Tupla4f colorDifuso, Tupla4f colorEspecular){
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    glLightfv(this->id, GL_AMBIENT, colorAmbiente);
    glLightfv(this->id, GL_DIFFUSE, colorDifuso);
    glLightfv(this->id, GL_SPECULAR, colorEspecular);
}

void Luz::setPosicion(Tupla4f posicion){
    this->posicion = posicion;

    glLightfv(this->id, GL_POSITION, posicion);
}