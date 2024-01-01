#ifndef CAMARA_H_INCLUDE
#define CAMARA_H_INCLUDE

#include "auxiliar.h"

typedef enum {PERSPECTIVA, ORTOGONAL} tipoCamara;
typedef enum {INACTIVO, PRIMERA_PERSONA, EXAMINAR} estadoRaton;

const int LIMITE = 5000;

class Camara{
private:
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    tipoCamara tipo;
    estadoRaton estado;

    float left, right;
    float bottom, top;
    float near, far;

    int anteriorX, anteriorY, anteriorZ;

public:
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left,
           float right, float bottom, float top, float near, float far);

    void setObserver();
    void setProyeccion(float width, float height);
    void setObjetivo(Tupla3f eye, Tupla3f at);
    void setAt(Tupla3f at);
    void setEstadoRaton(estadoRaton estado);

    void mover(float x, float y, float z, bool raton);
    void zoom(float factor, float width, float height);

    void rotarXExaminar(float angle, bool raton);
    void rotarYExaminar(float angle, bool raton);
    void rotarZExaminar(float angle, bool raton);

    void rotarXPrimeraPersona(float angle, bool raton);
    void rotarYPrimeraPersona(float angle, bool raton);
    void rotarZPrimeraPersona(float angle, bool raton);
};

#endif