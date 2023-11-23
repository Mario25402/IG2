#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "piramidepentagonal.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION} menu;
typedef enum {CUBO, PIRAMIDE, NINGUNO} objeto;

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

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    menu modoMenu = NADA;
    objeto obj = NINGUNO;

    // Objetos de la escena
    Ejes ejes;
    Cubo *cubo = nullptr;                   // es importante inicializarlo a 'nullptr'
    PiramidePentagonal *piramide = nullptr; // es importante inicializarlo a 'nullptr'

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
