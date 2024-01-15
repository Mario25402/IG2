#include "cilindro.h"
#include "esfera.h"

class BarraSuperior{
    private:
        Cilindro *cilindro;
        Cilindro *cilindro2;
        Esfera *esfera;

    public:
        BarraSuperior();

        void draw(bool puntos, bool alambre, bool solido);
        
        void setTextura();
        void setMaterial(Material *mat);
        void setSeleccionado(bool seleccionado);
};