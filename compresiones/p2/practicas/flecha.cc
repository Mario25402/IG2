#include "flecha.h"

// SE ACTIVA EN LA ESCENA EN EL MODO OBJETOS CON LA TECLA 'F'

Flecha3D::Flecha3D(float hPunta, float hAstil, float nRrev)
{
    float radioAstil = 10.0f;
    float radioPunta = 40.0f;
    float hTotal = hPunta + hAstil;

    std::vector<Tupla3f> perfil;
    perfil.push_back(Tupla3f(0, 0, 0));
    perfil.push_back(Tupla3f(radioAstil, 0, 0));
    perfil.push_back(Tupla3f(radioAstil, hAstil, 0));
    perfil.push_back(Tupla3f(radioPunta, hAstil, 0));
    perfil.push_back(Tupla3f(0, hTotal, 0));

    crearMalla(perfil, 30);
}