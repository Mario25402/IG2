#include "hier_brazos_eje.h"
#include "hier_asiento_giratorio.h"

class Atraccion{
    private:
        BrazosEje *brazosEje;
        AsientoGiratorio *asientoGiratorio;

        float rotacion;

    public:
        Atraccion();

        void animar(float velAnimacion);
        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setSeleccionado(bool seleccionado);
        void setVelocidad(float despBarra, float rotAsiento);
};