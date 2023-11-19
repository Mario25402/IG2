#include "hier_soporte.h"
#include "hier_brazo.h"
#include "hier_eje.h"

class ModeloJerarquico{
    private:    
        //Pie *pie;
        //Soporte *soporte;
        Brazo *brazo;
        Eje *eje;

    public:
        ModeloJerarquico();
        void draw(bool puntos, bool alambre, bool solido);
};