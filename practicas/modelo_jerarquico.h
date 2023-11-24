#include "hier_soporte.h"
#include "hier_atraccion.h"

class ModeloJerarquico{
    private:    
        Soporte *soporte;
        Atraccion *atraccion;

        int rotacion;

    public:
        ModeloJerarquico();

        void animar();
        void draw(bool puntos, bool alambre, bool solido);
};