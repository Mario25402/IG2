#include "hier_asiento.h"

Asiento::Asiento(){
    translacion = 0;
    acercando = false;

    cubo = new Cubo(50);
    suelo = new Cuadro(100);
    barra = new Barra();
}

void Asiento::draw(bool puntos, bool alambre, bool solido){
    // Respaldo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, -25);
        glScalef(3.5, 2, 0.5);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Asiento
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, 0);
        glScalef(3.5, 1, 0.5);

        cubo->draw(puntos, false, false);
        cubo->draw(false, alambre, false);
        cubo->draw(false, false, solido);
    glPopMatrix();

    // Suelo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(270, 1, 0, 0);

        suelo->draw(puntos, false, false);
        suelo->draw(false, alambre, false);
        suelo->draw(false, false, solido);
    glPopMatrix();

    // Barra de Seguridad
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0, 5, 45 + translacion);

        barra->draw(puntos, alambre, solido);
    glPopMatrix();
}

void Asiento::animar(float velAnimacion){
    if (acercando){
        translacion -= 0.2 * velAnimacion;

        if (translacion <= -20)
            acercando = false;
    }

    else{
        translacion += 0.2 * velAnimacion;

        if (translacion >= 0)
            acercando = true;
    }
}

void Asiento::setVelocidad(float despBarra){
    translacion = despBarra;
}

void Asiento::setSeleccionado(bool seleccionado){
    cubo->setSeleccionado(seleccionado);
    barra->setSeleccionado(seleccionado);
}

void Asiento::setMaterial(Material *mat){
    cubo->setMaterial(mat);
    barra->setMaterial(mat);
}

void Asiento::setTextura(){
    cubo->setTextura("../texturas/tela.jpg");
    suelo->setTextura("../texturas/metal.jpg");
    barra->setTextura();
}