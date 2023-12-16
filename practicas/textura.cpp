#include "textura.h"

Textura::Textura(string archivo){
    pimg = new jpg::Imagen(archivo);
    
    textura_id = 0;
    cargada = false;
    width = pimg->tamX();
    height = pimg->tamY();
    data = pimg->leerPixels();
}

/********************************************/

void Textura::activar(){
    if (!glIsEnabled(GL_TEXTURE_2D))
        glEnable(GL_TEXTURE_2D);

    glBindTexture ( GL_TEXTURE_2D , textura_id  );

    if (!cargada){
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        cargada = true;
    }
}

/********************************************/

void Textura::desactivar(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &textura_id);

    if (glIsEnabled(GL_TEXTURE_2D))
        glDisable(GL_TEXTURE_2D);
}

/********************************************/

void Textura::setId(int id){
    textura_id = id;

    glGenTextures(1, &textura_id);
}