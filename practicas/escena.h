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
#include "cuadro.h"

typedef enum {NADA, OBJETO, VISUALIZACION} menu;
typedef enum {JERARQUICO, ESFERA, CUADRO, NINGUNO} objeto;
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
    Cuadro *cuadro = nullptr;

    ModeloJerarquico *modelo = nullptr;

    // Objetos de iluminación
    LuzPosicional *luzPos = nullptr;
    LuzDireccional *luzDir = nullptr;

    // Variables relacionadas con el material
    Material *matBlanco = nullptr;

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

    // Variables de poscion de la luz 1
    float angulo = 0;
    float x = 50, y, z;

    // Componentes de color de la luz 2
    Tupla4f colorAmbiente = {0.2,0.2,0.2,1};
    Tupla4f colorDifuso = {0.4,0.4,0.4,1};
    Tupla4f colorEspecular = {0.4,0.4,0.4,1};

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
    void animarLuzPosicional();
    void animarLuzDireccional();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};

#endif
