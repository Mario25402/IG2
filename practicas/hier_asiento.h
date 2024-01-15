#include "cubo.h"
#include "cuadro.h"
#include "hier_barra.h"

class Asiento{
    private:
        Cubo *cubo;
        Cuadro *suelo;
        Barra *barra;

        float translacion;
        bool acercando;

    public:
        Asiento();

        void animar(float velAnimacion);
        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setVelocidad(float despBarra);
        void setSeleccionado(bool seleccionado);
};