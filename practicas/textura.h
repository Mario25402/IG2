#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "jpg_imagen.hpp"
#include "auxiliar.h"
#include "GL/gl.h"

using namespace std;

class Textura{
    private:
        bool cargada;
        int width, height;
        unsigned char *data;

        GLuint textura_id;
        jpg::Imagen *pimg;

    public:
        Textura(string archivo);

        void activar();
        void desactivar();
        void setId(int id);
};

#endif