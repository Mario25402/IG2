#include "luz.h"

void Luz::activar()
{
    if (glIsEnabled(GL_LIGHT0 + id) == GL_FALSE){
        // Crear la luz
        glLightfv(GL_LIGHT0 + id, GL_AMBIENT, colorAmbiente);
        glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, colorDifuso);
        glLightfv(GL_LIGHT0 + id, GL_SPECULAR, colorEspecular);
        glLightfv(GL_LIGHT0 + id, GL_POSITION, posicion);

        // Activar la luz
        glEnable(GL_LIGHT0 + id);
    }
}

void Luz::desactivar()
{
    if (glIsEnabled(GL_LIGHT0 + id) == GL_TRUE)
        glDisable(GL_LIGHT0 + id);

}