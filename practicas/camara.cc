#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left,
               float right, float bottom, float top, float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;

    this->tipo = (tipoCamara) tipo;
    estado = PRIMERA_PERSONA;

    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->near = near;
    this->far = far;
}

void Camara::setObserver(){
    gluLookAt(eye[0], eye[1], eye[2],
               at[0],  at[1],  at[2],
               up[0],  up[1],  up[2]);
}

void Camara::setProyeccion(float width, float height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspecto = width / height;

    if(tipo == ORTOGONAL)
        if (aspecto >= 1)
            glOrtho(left * aspecto, right * aspecto, bottom, top, near, far);
        else
            glOrtho(left, right, bottom / aspecto, top / aspecto, near, far);
    else
        if (aspecto >= 1)
            glFrustum(left * aspecto, right * aspecto, bottom, top, near, far);
        else
            glFrustum(left, right, bottom / aspecto, top / aspecto, near, far);

    glMatrixMode(GL_MODELVIEW);
}

void Camara::setObjetivo(Tupla3f eye, Tupla3f at){
    this->eye = eye;
    setAt(at);
}

void Camara::setEstadoRaton(estadoRaton estado){
    this->estado = estado;
}

void Camara::setAt(Tupla3f at){
    this->at = at;
}

void Camara::zoom(float factor, float width, float height){
    if (factor > 0){
        left *= factor;
        right *= factor;
        bottom *= factor;
        top *= factor;
    }
    else{
        left /= -factor;
        right /= -factor;
        bottom /= -factor;
        top /= -factor;
    }

    setProyeccion(width, height);
}

void Camara::mover(float x, float y, float z){
    if (estado == PRIMERA_PERSONA){
        rotarXPrimeraPersona(x);
        rotarYPrimeraPersona(y);
        rotarZPrimeraPersona(z);
    }

    else if (estado == EXAMINAR){
        if (x != 0) rotarXExaminar(x);
        if (y != 0) rotarYExaminar(y);
        if (z != 0) rotarZExaminar(z);
    }
}

/*****************************************************************************/

void Camara::rotarXPrimeraPersona(float angle){
    eye[0] += angle;
}

void Camara::rotarYPrimeraPersona(float angle){
    eye[1] += angle;
}

void Camara::rotarZPrimeraPersona(float angle){
    eye[2] += angle;
}

/*****************************************************************************/

void Camara::rotarXExaminar(float angle) {
    angle /= 50;
    angle = fmod(angle, 360);

    float radio = 100;

    eye[0] = at[0] + radio * cos(angle);
    eye[2] = at[2] + radio * sin(angle);
}

void Camara::rotarYExaminar(float angle) {
    angle /= 50;
    angle = fmod(angle, 360);

    float radio = 100;

    eye[1] = at[1] + radio * sin(angle);
    eye[2] = at[2] + radio * cos(angle);
}

void Camara::rotarZExaminar(float angle) {
    angle /= 50;
    angle = fmod(angle, 360);

    up[0] = sin(angle);
    up[1] = cos(angle);
}