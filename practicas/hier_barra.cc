#include "hier_barra.h"

Barra::Barra(){
    cilindro = new Cilindro(4, 20, 10, 5);
    barraSuperior = new BarraSuperior();
}

void Barra::draw(bool puntos, bool alambre, bool solido){
    // Centro
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScalef(0.5, 5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-65, 0, 0);
        glScalef(0.5, 5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(65, 0, 0);
        glScalef(0.5, 5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Barra superior
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 55, 0);

        barraSuperior->draw(puntos, alambre, solido);
    glPopMatrix();
}