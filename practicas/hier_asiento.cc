#include "hier_asiento.h"

Asiento::Asiento(){
    translacion = 0;
    acercando = true;

    cubo = new Cubo(50);
    barra = new Barra();
}

void Asiento::draw(bool puntos, bool alambre, bool solido){
    // Respaldo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, -25);
        glScalef(3.5, 2, 0.5);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Asiento
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, 0);
        glScalef(3.5, 1, 0.5);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Suelo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScalef(4, 0.1, 2);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Barra de Seguridad
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, 45 + translacion);

        barra->draw(puntos, alambre, solido);
    glPopMatrix();
}

void Asiento::animar(){
    if (acercando){
        translacion -= 0.2;

        if (translacion <= -20)
            acercando = false;
    }

    else{
        translacion += 0.2;

        if (translacion >= 0)
            acercando = true;
    }

    barra->animar();
}