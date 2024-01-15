#include "hier_brazo.h"

Brazo::Brazo(){
    cubo = new Cubo(10);
    cilindro = new Cilindro(4, 20, 25, 10);
}

void Brazo::draw(bool puntos, bool alambre, bool solido){
    // Panel
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0,-50,0);
        glScalef(120, 12, 2.5);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-600, 0, -12.5);
        glScalef(10, 10, 1);
        glRotatef(90, 1, 0, 0);

        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Centro
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 0, -12.5);
        glScalef(15, 15, 1);
        glRotatef(90, 1, 0, 0);

        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    // Derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(600, 0, -12.5);
        glScalef(10, 10, 1);
        glRotatef(90, 1, 0, 0);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();
}

void Brazo::setSeleccionado(bool seleccionado){
    cubo->setSeleccionado(seleccionado);
    cilindro->setSeleccionado(seleccionado);
}

void Brazo::setMaterial(Material *mat){
    cubo->setMaterial(mat);
    cilindro->setMaterial(mat);
}

void Brazo::setTextura(){
    cubo->setTextura("../texturas/oxido.jpg");
    cilindro->setTextura("../texturas/oxido.jpg");
}