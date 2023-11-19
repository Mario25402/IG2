#include "modelo_jerarquico.h"

ModeloJerarquico::ModeloJerarquico(){
    //pie = new Pie();
    //soporte = new Soporte();
    brazo = new Brazo();
    eje = new Eje();
}

void ModeloJerarquico::draw(bool puntos, bool alambre, bool solido){
    //pie->draw(puntos, alambre, solido);
    //soporte->draw(puntos, alambre, solido);
    //brazo->draw(puntos, alambre, solido);
    eje->draw(puntos, alambre, solido);
}