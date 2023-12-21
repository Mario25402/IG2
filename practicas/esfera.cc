#include "auxiliar.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera (int num_vert_perfil, int num_instancias_perf, float r){
    perfil.resize(num_vert_perfil);
    radio = r;

    for (int i = 0; i < num_vert_perfil; i++){
        perfil[i] = Tupla3f(radio * cos(2*M_PI*i / (num_vert_perfil-1)), radio * sin(2*M_PI*i / (num_vert_perfil-1)), 0);
    }

    crearMalla(perfil, num_instancias_perf, true);
    calcularNormales();
}

float Esfera::getRadio(){
    return radio;
}