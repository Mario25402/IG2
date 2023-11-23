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
#include "flecha.h"
#include "luz.h"
#include "luzPosicional.h"
#include "luzDireccional.h"
#include "ejesFlechas.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION} menu;
typedef enum {CUBO, PIRAMIDE, PLY, CILINDRO, ESFERA, CONO, MULTIPLE, VECTOR, FLECHA, NINGUNO} objeto;
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

    // Selección de opciones
    menu modoMenu = NADA;
    objeto obj = NINGUNO;
    objPly objPlySel = NONE;

    /////

    // Objetos de la escena, importante inicializarlos a nullptr
    Ejes ejes;
    EjesFlechas *ejesFlecha = nullptr;

    Cubo *cubo = nullptr;
    PiramidePentagonal *piramide = nullptr;

    Cilindro *cilindro = nullptr;
    Esfera *esfera = nullptr;
    Cono *cono = nullptr;

    Flecha3D *flecha = nullptr;

    ObjRevolucion *ply1 = nullptr;
    ObjPLY *ply2 = nullptr;
    ObjPLY *ply3 = nullptr;
    ObjRevolucion *rev = nullptr;

    // Objetos de iluminación
    LuzPosicional *luzPos = nullptr;
    LuzDireccional *luzDir = nullptr;

    /////       

    // Variables de estado de visualización
    bool puntos = false;
    bool alambre = false;
    bool solido = true;

    // Variables relacionadas con la iliuminación
    bool iluminado = false;

    bool alfa = false;
    bool beta = false;
    
    float angulo_alfa = 0;
    float angulo_beta = 0;

    bool luz1 = false;
    bool luz2 = false;

    // Variables relacionadas con el material
    Material *bronce = nullptr;
    Material *oro = nullptr;
    Material *perla = nullptr;

    Material *matBlanco = nullptr;
    Material *matNegro = nullptr;

    /////

    void init_objetos();
    void init_luces();
    void init_materiales();

    void draw_objects();
    void draw_axis();
    void draw_lights();
    

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
