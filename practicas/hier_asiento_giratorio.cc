#include "hier_asiento_giratorio.h"

AsientoGiratorio::AsientoGiratorio(){
    asiento = new Asiento();
    cilindro = new Cilindro(4, 20, 10, 10);
}

void AsientoGiratorio::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

        asiento->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(97.5, 90, -25);
        glRotatef(90, 0, 0, 1);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-87.5, 90, -25);
        glRotatef(90, 0, 0, 1);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();
}