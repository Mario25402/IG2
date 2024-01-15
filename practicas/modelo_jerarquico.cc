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

void ModeloJerarquico::animar(float velAnimacion){        
    atraccion->animar(velAnimacion);

    rotacion += 5 * velAnimacion;
    rotacion = (int)rotacion % 360;
}

void ModeloJerarquico::setVelocidad(float despBarra, float rotAsiento, float rotAtraccion){
    rotacion = rotAtraccion;

    atraccion->setVelocidad(despBarra, rotAsiento);
}

void ModeloJerarquico::setSeleccionado(bool seleccionado){
    atraccion->setSeleccionado(seleccionado);
    soporte->setSeleccionado(seleccionado);
}

void ModeloJerarquico::setMaterial(Material *mat){
    atraccion->setMaterial(mat);
    soporte->setMaterial(mat);
}

void ModeloJerarquico::setTextura(){
    atraccion->setTextura();
    soporte->setTextura();
}