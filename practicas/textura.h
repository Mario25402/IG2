#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "jpg_imagen.hpp"
#include "auxiliar.h"
#include "GL/gl.h"

using namespace std;

class Textura{
    private:
        GLuint textura_id;
        int width, height;

        jpg::Imagen *pimg;
        unsigned char *data;

    public:
        Textura(string archivo);

        void activar();
        void desactivar();
};

#endif