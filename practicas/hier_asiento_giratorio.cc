#include "hier_asiento_giratorio.h"

AsientoGiratorio::AsientoGiratorio(){
    asiento = new Asiento();
    cilindro = new Cilindro(4, 20, 10, 10);
}

void AsientoGiratorio::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, -90, 25);
        glScalef(0.6, 1, 1);

        asiento->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(77.5, 0, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(1, 3, 1);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-47.5, 0, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(1, 3, 1);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();
}

void AsientoGiratorio::animar(float velAnimacion){
    asiento->animar(velAnimacion);
}

void AsientoGiratorio::setVelocidad(float despBarra){
    asiento->setVelocidad(despBarra);
}