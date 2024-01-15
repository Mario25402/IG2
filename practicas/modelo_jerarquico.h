#include "hier_soporte.h"
#include "hier_atraccion.h"

class ModeloJerarquico{
    private:    
        Soporte *soporte;
        Atraccion *atraccion;

        float rotacion;

    public:
        ModeloJerarquico();

        void animar(float velAnimacion);
        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setSeleccionado(bool seleccionado);
        void setVelocidad(float despBarra, float rotAsiento, float rotAtraccion);
};