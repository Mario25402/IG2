#include "hier_soporte.h"
#include "hier_atraccion.h"

class ModeloJerarquico{
    private:    
        Soporte *soporte;
        Atraccion *atraccion;

        float rotacion;

    public:
        ModeloJerarquico();

        void draw(bool puntos, bool alambre, bool solido);
        void animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion);
        void setVelocidad(float velBarra, float velAsiento, float velAtraccion);
};