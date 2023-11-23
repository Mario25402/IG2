#include "hier_brazos_eje.h"

BrazosEje::BrazosEje(){
    brazo = new Brazo();
    eje = new Eje();
}

void BrazosEje::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-250,0,0);
        glRotatef(90,0,1,0);

        brazo->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        eje->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(250,0,0);
        glRotatef(90,0,1,0);

        brazo->draw(puntos, alambre, solido);
    glPopMatrix();
}