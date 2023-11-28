#include "modelo_jerarquico.h"

ModeloJerarquico::ModeloJerarquico(){
    rotacion = 0;

    soporte = new Soporte();
    atraccion = new Atraccion();
}

void ModeloJerarquico::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 1100, 0);
        glRotatef(rotacion, 1, 0, 0);
        glScalef(0.96, 1, 1);

        atraccion->draw(puntos, alambre, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        soporte->draw(puntos, alambre, solido);
    glPopMatrix();

}

void ModeloJerarquico::animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion){        
    atraccion->animar(turnoBarra, turnoAsiento, turnoAtraccion);

    if (turnoAtraccion)
        rotacion += 5 % 360;
}