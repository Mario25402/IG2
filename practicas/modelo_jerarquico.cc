#include "modelo_jerarquico.h"

ModeloJerarquico::ModeloJerarquico(){
    soporte = new Soporte();
    brazosEje = new BrazosEje();
    asientoGiratorio = new AsientoGiratorio();
}

void ModeloJerarquico::draw(bool puntos, bool alambre, bool solido){
    /*glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 875, 0);

        brazosEje->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        soporte->draw(puntos, alambre, solido);
    glPopMatrix();*/

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        asientoGiratorio->draw(puntos, alambre, solido);
    glPopMatrix();
}