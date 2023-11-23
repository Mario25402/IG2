#include "hier_soporte.h"

Soporte::Soporte(){
    pie = new Pie();
    cubo = new Cubo();
}

void Soporte::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(300, 0, 0);

        pie->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-300, 0, 0);
        
        pie->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScalef(900, 1, 600);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();
}