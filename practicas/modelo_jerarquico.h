#include "hier_soporte.h"
#include "hier_brazos_eje.h"
#include "hier_asiento_giratorio.h"

class ModeloJerarquico{
    private:    
        Soporte *soporte;
        BrazosEje *brazosEje;
        AsientoGiratorio *asientoGiratorio;

    public:
        ModeloJerarquico();
        void draw(bool puntos, bool alambre, bool solido);
};