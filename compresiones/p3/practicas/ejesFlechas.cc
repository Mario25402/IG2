#include "ejesFlechas.h"

EjesFlechas::EjesFlechas()
{
    fx = new Flecha3D(50, 500);
    fy = new Flecha3D(50, 500);
    fz = new Flecha3D(50, 500);

    // ambiente difuso especular brillo
    mx = new Material({0.4,0,0,1}, {0.6,0,0,1}, {1,0,0,1}, 128);
    my = new Material({0,0.4,0,1}, {0,0.6,0,1}, {0,1,0,1}, 128);
    mz = new Material({0,0,0.4,1}, {0,0,0.6,1}, {0,0,1,1}, 128);
}

void EjesFlechas::draw(bool puntos, bool alambre, bool solido, int color)
{
    // Flecha Eje X
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(-90,0,0,1);

        fx->setMaterial(mx);
        fx->draw(puntos, false, false, 1);
        fx->draw(false, alambre, false, 1);
        fx->draw(false, false, solido, 1);
    glPopMatrix();

    // Flecha Eje Y
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        fy->setMaterial(my);
        fy->draw(puntos, false, false, 2);
        fy->draw(false, alambre, false, 2);
        fy->draw(false, false, solido, 2);
    glPopMatrix();

    // Flecha Eje Z
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(90,1,0,0);

        fz->setMaterial(mz);
        fz->draw(puntos, false, false, 3);
        fz->draw(false, alambre, false, 3);
        fz->draw(false, false, solido, 3);
    glPopMatrix();
}