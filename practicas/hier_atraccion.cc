#include "hier_atraccion.h"

Atraccion::Atraccion(){
    brazosEje = new BrazosEje();
    asientoGiratorio = new AsientoGiratorio();

    rotacion = 0;
    vueltas = -1;
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

void Atraccion::animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion){
    asientoGiratorio->animar(turnoBarra, turnoAsiento, turnoAtraccion);

    if (turnoAsiento){
        if (rotacion == 0)
            vueltas++;

        rotacion = (((int)rotacion - 10) % 360);

        if (vueltas == 2){
            vueltas = -1;

            turnoAsiento = false;
            turnoAtraccion = false;
            turnoBarra = true;
        }
    }
}