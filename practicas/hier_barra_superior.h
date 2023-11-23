#include "cilindro.h"
#include "esfera.h"

class BarraSuperior{
    private:
        Cilindro *cilindro;
        Esfera *esfera;

    public:
        BarraSuperior();
        void draw(bool puntos, bool alambre, bool solido);
};