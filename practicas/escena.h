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
#include "camara.h"
#include "tetraedro.h"

typedef enum {NADA, VISUALIZACION, CAMARA} menu;
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
    movimiento move = NONE;

    /////

    // Variables de la camara
    Camara *camaras[4] = {nullptr};

    // Objetos de la escena, importante inicializarlos a nullptr
    Ejes ejes;

    ObjPLY *ply = nullptr;
    ObjRevolucion *peon = nullptr;
    ObjRevolucion *copa = nullptr;

    Cono *cono = nullptr;
    Cuadro *cuadro = nullptr;
    Esfera *esfera = nullptr;
    ModeloJerarquico *modelo = nullptr;

    Cubo *cuboR = nullptr;
    Cubo *cuboG = nullptr;
    Cubo *cuboB = nullptr;
    Cubo *cuboW = nullptr;

    Tetraedro *tetraedro = nullptr;

    // Objetos de iluminación
    LuzPosicional *luzPos = nullptr;
    LuzDireccional *luzDir = nullptr;

    LuzDireccional *luzRoja = nullptr;
    LuzDireccional *luzVerde = nullptr;
    LuzDireccional *luzAzul = nullptr;
    LuzDireccional *luzBlanca = nullptr;

    // Variables relacionadas con el material
    Material *matCromado = nullptr;
    Material *matCyan = nullptr;
    Material *matRojo = nullptr;

    /////       

    // Variables de estado de visualización
    bool puntos = false;
    bool alambre = false;
    bool solido = true;

    // Variables relacionadas con la iliuminación
    bool iluminado = true;

    bool alfa = false;
    bool beta = false;
    
    float angulo_alfa = 0.0f;
    float angulo_beta = 0.0f;

    float alfaFocos;
    float betaFocos;

    bool luz1 = false;
    bool luz2 = false;

    // Variables de moviemiento de la animación
    bool animacion = true;
    bool manual = false;

    bool animacionDireccional = true;
    bool animacionPosicional = true;

    // Movimiento
    float velAnimacion = 1.0f;
    float velBarra = 0.0f;
    float velAsiento = 0.0f;
    float velAtraccion = 0.0f;
    float avance = 0.0f;

    // Variables de selección y camara
    int activa = 3;
    int seleccionado = 0;
    int xant = 0, yant = 0;
    bool clickDer = false;

    /////

    void init_camaras();
    void init_objetos();
    void init_luces();
    void init_materiales();

    void draw_objects();
    void draw_axis();
    void draw_lights();

    void pick(int x, int y);
    void dibujarSeleccion(int selected);
    void procesarHits(GLint hits, GLuint buffer[]);

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
    void animarGema();
    void animarFocos();

    // Interacción con la escena por teclado
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    // Interacción con la escena por ratón
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
};

#endif
