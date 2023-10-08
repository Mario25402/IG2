#include "auxiliar.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float h, float r){
    radio = r;
    altura = h;
    perfil.resize(num_vert_perfil);

    perfil[0] = Tupla3f(0.0f, 0.0f, 0.0f);
    perfil[1] = Tupla3f(r, 0.0f, 0.0f);
    perfil[num_vert_perfil-1] = Tupla3f(0.0f, h, 0.0f);

    if (num_vert_perfil > 3){
        for (int i = 1; i < num_instancias_perf-1; i++){
            perfil[i] = Tupla3f(r / (num_instancias_perf-i-3), h / (num_instancias_perf-i-3), 0.0f);
        }
    }

    crearMalla(perfil, num_instancias_perf);
}