#include "cubo.h"
#include "hier_barra.h"

class Asiento{
    private:
        Cubo *cubo;
        Barra *barra;

        float translacion;
        bool acercando;

    public:
        Asiento();

        void animar(float velAnimacion);
        void setVelocidad(float despBarra);
        void draw(bool puntos, bool alambre, bool solido);
};