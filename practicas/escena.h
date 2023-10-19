#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "piramidepentagonal.h"
#include "objply.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION} menu;
typedef enum {CUBO, PIRAMIDE, PLY, CILINDRO, ESFERA, CONO, MULTIPLE, VECTOR, NINGUNO} objeto;
typedef enum {PLY1, PLY2, PLY3, NONE} objPly;

class Escena
{
private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    /////

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    /////

    // Selección de teclas
    menu modoMenu = NADA;
    objeto obj = NINGUNO;
    objPly objPlySel = NONE;

    /////

    // Objetos de la escena, importante inicializarlos a nullptr
    Ejes ejes;
    Cubo *cubo = nullptr;
    PiramidePentagonal *piramide = nullptr;

    Cilindro *cilindro = nullptr;
    Esfera *esfera = nullptr;
    Cono *cono = nullptr;    

    ObjRevolucion *ply1 = nullptr;
    ObjPLY *ply2 = nullptr;
    ObjPLY *ply3 = nullptr;
    ObjRevolucion *rev = nullptr;

    /////       

    // Variables de estado de visualización
    bool puntos = false;
    bool alambre = false;
    bool solido = true;

public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};

#endif
