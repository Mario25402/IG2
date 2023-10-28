#include "auxiliar.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float h, float r){
    radio = r;
    altura = h;

    perfil.push_back(Tupla3f(0.0f, 0.0f, 0.0f));    // base central
    perfil.push_back(Tupla3f(r, 0.0f, 0.0f));       // base derecha
    perfil.push_back(Tupla3f(0.0f, h, 0.0f));       // superior

    // resto de vértices
    /*if (num_vert_perfil > 3){
        for (int i = 2; i < num_vert_perfil-1; i++){
            perfil.push_back(Tupla3f(r - (r / (num_vert_perfil-i)), h / (num_vert_perfil-i), 0.0f));
        }    
    }*/

    crearMalla(perfil, num_instancias_perf);
    calcularNormales();
}