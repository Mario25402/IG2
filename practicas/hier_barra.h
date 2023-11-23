#include "hier_barra_superior.h"

class Barra{
    private:
        Cilindro *cilindro;
        BarraSuperior *barraSuperior;
    
    public:
        Barra();
        void draw(bool puntos, bool alambre, bool solido);
};