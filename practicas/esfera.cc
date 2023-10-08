#include "auxiliar.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera (int num_vert_perfil, int num_instancias_perf, float r){
    perfil.resize(num_vert_perfil);
    radio = r;
}