#include "hier_atraccion.h"

Atraccion::Atraccion(){
    brazosEje = new BrazosEje();
    asientoGiratorio = new AsientoGiratorio();

    rotacion = 0;
}

void Atraccion::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        brazosEje->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 0, -600);
        glScalef(3, 3, 3);
        glRotatef(rotacion, 1, 0, 0);

        asientoGiratorio->draw(puntos, alambre, solido);
    glPopMatrix();
}

void Atraccion::animar(float velAnimacion){
    asientoGiratorio->animar(velAnimacion);

    rotacion -= 10 * velAnimacion;
    rotacion = (int)rotacion % 360;
}

void Atraccion::setVelocidad(float despBarra, float rotAsiento){
    rotacion = rotAsiento;

    asientoGiratorio->setVelocidad(despBarra);
}

void Atraccion::setSeleccionado(bool seleccionado){
    brazosEje->setSeleccionado(seleccionado);
    asientoGiratorio->setSeleccionado(seleccionado);
}

void Atraccion::setMaterial(Material *mat){
    brazosEje->setMaterial(mat);
    asientoGiratorio->setMaterial(mat);
}

void Atraccion::setTextura(){
    brazosEje->setTextura();
    asientoGiratorio->setTextura();
}