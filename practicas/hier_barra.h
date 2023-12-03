#include "hier_barra_superior.h"

class Barra{
    private:
        Cilindro *cilindro;
        BarraSuperior *barraSuperior;

        //float rotacion;
        //bool bajando;
    
    public:
        Barra();

        void draw(bool puntos, bool alambre, bool solido);
        //void animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion);
};