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
#include "luz.h"
#include "luzPosicional.h"
#include "luzDireccional.h"
#include "modelo_jerarquico.h"

typedef enum {NADA, OBJETO, VISUALIZACION} menu;
typedef enum {JERARQUICO, ESFERA, CUBO, NINGUNO} objeto;
//typedef enum {PLY1, PLY2, PLY3, NONE} objPly;
typedef enum {BARRA, ASIENTO, ATRACCION, NONE} movimiento;

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
    //objPly objPlySel = NONE;
    movimiento move = NONE;

    /////

    // Objetos de la escena, importante inicializarlos a nullptr
    Ejes ejes;
    Cubo *cubo = nullptr;
    Esfera *esfera = nullptr;

    /*PiramidePentagonal *piramide = nullptr;
    Cilindro *cilindro = nullptr;
    Cono *cono = nullptr;    

    ObjRevolucion *ply1 = nullptr;
    ObjPLY *ply2 = nullptr;
    ObjPLY *ply3 = nullptr;
    ObjRevolucion *rev = nullptr;*/

    ModeloJerarquico *modelo = nullptr;

    // Objetos de iluminación
    LuzPosicional *luzPos = nullptr;
    LuzDireccional *luzDir = nullptr;

    // Variables relacionadas con el material
    Material *bronce = nullptr;
    Material *oro = nullptr;
    Material *perla = nullptr;

    Material *matBlanco = nullptr;
    Material *matNegro = nullptr;

    /////       

    // Variables de estado de visualización
    bool puntos = false;
    bool alambre = true;
    bool solido = true;

    // Variables relacionadas con la iliuminación
    bool iluminado = false;

    bool alfa = false;
    bool beta = false;
    
    float angulo_alfa = 0.0f;
    float angulo_beta = 0.0f;

    bool luz1 = false;
    bool luz2 = false;

    // Variables de moviemiento de la animación
    bool animacion = false;
    bool manual = false;

    // Movimiento
    float velAnimacion = 1.0f;
    float velBarra = 0.0f;
    float velAsiento = 0.0f;
    float velAtraccion = 0.0f;

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

    // Animación
    void animarModeloJerarquico();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};

#endif
