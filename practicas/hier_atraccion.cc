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

void Atraccion::animar(){
    rotacion -= 5 % 360;
    asientoGiratorio->animar();
}