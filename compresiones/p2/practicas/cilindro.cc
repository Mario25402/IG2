#include "auxiliar.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro (int num_vert_perfil, int num_instancias_perf, float h, float r){
    radio = r;
    altura = h;

    perfil.push_back(Tupla3f(0.0f, 0.0f, 0.0f));    // base inferior
    perfil.push_back(Tupla3f(r, 0.0f, 0.0f));       // lateral inferior
    perfil.push_back(Tupla3f(r, h, 0.0f));          // lateral superior
    perfil.push_back(Tupla3f(0.0f, h, 0.0f));       // base superior
    
    // resto de vértices
    /*if (num_vert_perfil > 4){
        for (int i = 2; i < num_vert_perfil-2; i++){
            perfil.push_back(Tupla3f(r, h / (num_vert_perfil-i-2), 0.0f));
        }
    }*/

    crearMalla(perfil, num_instancias_perf);
}