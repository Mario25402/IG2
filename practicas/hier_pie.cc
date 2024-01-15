#include "hier_pie.h"

Pie::Pie(){
    cubo = new Cubo(35);
    piramide = new PiramidePentagonal(50, 50);
}

void Pie::draw(bool puntos, bool alambre, bool solido){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScalef(2, 0.75, 2);
        
        piramide->draw(puntos, false, false);
        piramide->draw(false, alambre, false);
        piramide->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 37.5, 0);
        glScalef(2, 30, 2);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();
}

void Pie::setSeleccionado(bool seleccionado){
    cubo->setSeleccionado(seleccionado);
    piramide->setSeleccionado(seleccionado);
}

void Pie::setMaterial(Material *mat){
    cubo->setMaterial(mat);
    piramide->setMaterial(mat);
}

void Pie::setTextura(){
    cubo->setTextura("../texturas/metal.jpg");
    piramide->setTextura("../texturas/metal.jpg");
}