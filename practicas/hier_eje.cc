#include "hier_eje.h"

Eje::Eje(){
    cilindro = new Cilindro(4, 20, 10, 10);
}

void Eje::draw(bool puntos, bool alambre, bool solido){
    // Izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-350, 0, 0);
        glScalef(10, 5, 5);
        glRotatef(90, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();
    
    // Centro
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-250, 0, 0);
        glScalef(50, 0.5, 1);
        glRotatef(90, 0, 1, 0);
        glRotatef(90, 1, 0, 0);

        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(250, 0, 0);
        glScalef(10, 5, 5);
        glRotatef(90, 0, 1, 0);
        glRotatef(90, 1, 0, 0);

        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();
}