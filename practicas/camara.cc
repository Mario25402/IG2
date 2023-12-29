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
    this->at = at;
}

void Camara::setEstadoRaton(estadoRaton estado){
    this->estado = estado;
}

estadoRaton Camara::getEstadoRaton(){
    return this->estado;
}

Tupla3f Camara::getEye(){
    return eye;
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
        rotarXExaminar(y); // teclas
        rotarYExaminar(x); // alternadas
        rotarZExaminar(z);
    }

    setObserver();
}

/*****************************************************************************/

void Camara::rotarXPrimeraPersona(float angle){
    if (-500 <= eye[0] and eye[0] <= 500)
        eye[0] += angle;
}

void Camara::rotarYPrimeraPersona(float angle){
    if (-500 <= eye[1] and eye[1] <= 500)
        eye[1] += angle;
}

void Camara::rotarZPrimeraPersona(float angle){
    if (-500 <= eye[2] and eye[2] <= 500)
        eye[2] += angle;
}

void Camara::rotarXExaminar(float angle) {
    // Calcular vector de dirección desde el 'eye' al 'at'
    float dirX = at[0] - eye[0];
    float dirY = at[1] - eye[1];
    float dirZ = at[2] - eye[2];

    // Calcular el ángulo en radianes
    float theta = angle * M_PI / 180.0f;

    // Rotación en el eje X
    eye[1] = at[1] + dirY * cos(theta) - dirZ * sin(theta);
    eye[2] = at[2] + dirY * sin(theta) + dirZ * cos(theta);
}

void Camara::rotarYExaminar(float angle) {
    // Calcular vector de dirección desde el 'eye' al 'at'
    float dirX = at[0] - eye[0];
    float dirY = at[1] - eye[1];
    float dirZ = at[2] - eye[2];

    // Calcular el ángulo en radianes
    float theta = angle * M_PI / 180.0f;

    // Rotación en el eje Y
    eye[0] = at[0] + dirX * cos(theta) + dirZ * sin(theta);
    eye[2] = at[2] - dirX * sin(theta) + dirZ * cos(theta);
}

void Camara::rotarZExaminar(float angle) {
    // Calcular vector de dirección desde el 'eye' al 'at'
    float dirX = at[0] - eye[0];
    float dirY = at[1] - eye[1];
    float dirZ = at[2] - eye[2];

    // Calcular el ángulo en radianes
    float theta = angle * M_PI / 180.0f;

    // Rotación en el eje Z
    eye[0] = at[0] + dirX * cos(theta) - dirY * sin (theta);
    eye[1] = at[1] + dirX * sin(theta) + dirY * cos(theta);
}