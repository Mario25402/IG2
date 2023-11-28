#include "hier_brazos_eje.h"
#include "hier_asiento_giratorio.h"

class Atraccion{
    private:
        BrazosEje *brazosEje;
        AsientoGiratorio *asientoGiratorio;

        float rotacion;
        int vueltas;

    public:
        Atraccion();

        void draw(bool puntos, bool alambre, bool solido);
        void animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion);
};