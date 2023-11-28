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

        void draw(bool puntos, bool alambre, bool solido);
        void animar(bool &turnoBarra, bool &turnoAsiento, bool &turnoAtraccion);
};