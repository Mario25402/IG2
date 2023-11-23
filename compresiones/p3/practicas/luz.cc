#include "luz.h"

void Luz::activar()
{
    if (glIsEnabled(id) == GL_FALSE){
        // Crear la luz
        glLightfv(id, GL_AMBIENT, colorAmbiente);
        glLightfv(id, GL_DIFFUSE, colorDifuso);
        glLightfv(id, GL_SPECULAR, colorEspecular);
        glLightfv(id, GL_POSITION, posicion);

        // Activar la luz
        glEnable(id);
    }
}

void Luz::desactivar()
{
    if (glIsEnabled(id) == GL_TRUE)
        glDisable(id);

}