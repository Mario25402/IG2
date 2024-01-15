#include "hier_soporte.h"

Soporte::Soporte(){
    pie = new Pie();
    suelo = new Cuadro(600);
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
        glRotatef(270, 1,0,0);

        suelo->draw(puntos, false, false);
        suelo->draw(false, alambre, false);
        suelo->draw(false, false, solido);
    glPopMatrix();
}

void Soporte::setSeleccionado(bool seleccionado){
    pie->setSeleccionado(seleccionado);
    suelo->setSeleccionado(seleccionado);
}

void Soporte::setMaterial(Material *mat){
    pie->setMaterial(mat);
    suelo->setMaterial(mat);
}

void Soporte::setTextura(){
    pie->setTextura();
    suelo->setTextura("../texturas/ladrillo.jpg");
}