#include "hier_pie.h"
#include "cuadro.h"

class Soporte{
    private:
        Pie *pie;
        Cuadro *suelo;

    public:
        Soporte();

        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setSeleccionado(bool seleccionado);
};