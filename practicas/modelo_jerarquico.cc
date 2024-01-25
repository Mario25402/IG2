#include "modelo_jerarquico.h"

ModeloJerarquico::ModeloJerarquico(){
    rotacion = 0;
    rotGema = 0;

    matGema = new Material({0,0.5,0,1}, {0,0.5,0,1}, {0,0.5,0,1}, 50);

    soporte = new Soporte();
    atraccion = new Atraccion();
    gema = new PiramidePentagonal(100, 100);

}

void ModeloJerarquico::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 1100, 0);
        glRotatef(rotacion, 1, 0, 0);
        glScalef(0.96, 1, 1);

        atraccion->draw(puntos, alambre, solido);
    glPopMatrix();

    glPushMatrix();
        soporte->draw(puntos, alambre, solido);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 2000, 0);
        glRotatef(rotGema, 0, 1, 0);
        gema->setMaterial(matGema);
        gema->draw(puntos, false, false);
        gema->draw(false, alambre, false);
        gema->draw(false, false, solido);
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

void ModeloJerarquico::animarGema(){
    rotGema++;
    rotGema %= 360;
}