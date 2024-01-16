#ifndef CAMARA_H_INCLUDE
#define CAMARA_H_INCLUDE

#include "auxiliar.h"

typedef enum {PERSPECTIVA, ORTOGONAL} tipoCamara;
typedef enum {INACTIVO, PRIMERA_PERSONA, EXAMINAR} estadoCamara;

const int LIMITE = 5000;

class Camara{
private:
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    tipoCamara tipo;
    estadoCamara estado;

    float left, right;
    float bottom, top;
    float near, far;

public:
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left,
           float right, float bottom, float top, float near, float far);

    void setObserver();
    void setProyeccion(float width, float height);
    void setObjetivo(Tupla3f eye, Tupla3f at);
    void setAt(Tupla3f at);
    void setUp(Tupla3f up);
    void setEstadoCamara(estadoCamara estado);

    Tupla3f getEye();
    estadoCamara getEstadoCamara();

    void mover(float x, float y, float z);
    void zoom(float factor, float width, float height);

    void rotarXPrimeraPersona(float angle);
    void rotarYPrimeraPersona(float angle);
    void rotarZPrimeraPersona(float angle);

    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);

};

#endif