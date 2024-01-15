#include "hier_barra_superior.h"

BarraSuperior::BarraSuperior(){
    cilindro = new Cilindro(4, 20, 10, 5);
    cilindro2 = new Cilindro(4, 20, 10, 5);
    esfera = new Esfera(20, 20, 5);
}

void BarraSuperior::draw(bool puntos, bool alambre, bool solido){
    // Centro
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glScalef(0.5, 2.5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();        
        esfera->draw(puntos, false, false);
        esfera->draw(false, alambre, false);
        esfera->draw(false, false, solido);
    glPopMatrix();

    // Izquierda
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-65, 0, 0);
        glScalef(0.5, 2.5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(-65, 0, 0);

        esfera->draw(puntos, false, false);
        esfera->draw(false, alambre, false);
        esfera->draw(false, false, solido);
    glPopMatrix();

    // Derecha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(65, 0, 0);
        glScalef(0.5, 2.5, 0.5);
        
        cilindro->draw(puntos, false, false);
        cilindro->draw(false, alambre, false);
        cilindro->draw(false, false, solido);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();       
        glTranslatef(65, 0, 0);

        esfera->draw(puntos, false, false);
        esfera->draw(false, alambre, false);
        esfera->draw(false, false, solido);
    glPopMatrix();

    // Arriba
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(75, 25, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(1,15,1);

        cilindro2->draw(puntos, false, false);
        cilindro2->draw(false, alambre, false);
        cilindro2->draw(false, false, solido);
    glPopMatrix();
}

void BarraSuperior::setSeleccionado(bool seleccionado){
    cilindro->setSeleccionado(seleccionado);
    esfera->setSeleccionado(seleccionado);
}

void BarraSuperior::setMaterial(Material *mat){
    cilindro->setMaterial(mat);
    esfera->setMaterial(mat);
}

void BarraSuperior::setTextura(){
    cilindro->setTextura("../texturas/metal.jpg");
    cilindro2->setTextura("../texturas/goma.jpg");
    esfera->setTextura("../texturas/metal.jpg");
}