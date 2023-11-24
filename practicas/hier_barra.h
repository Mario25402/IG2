#include "hier_barra_superior.h"

class Barra{
    private:
        Cilindro *cilindro;
        BarraSuperior *barraSuperior;

        float rotacion;
        bool bajando;
    
    public:
        Barra();

        void animar();
        void draw(bool puntos, bool alambre, bool solido);
};