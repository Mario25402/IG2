#include "cubo.h"
#include "hier_barra.h"

class Asiento{
    private:
        Cubo *cubo;
        Barra *barra;

    public:
        Asiento();
        void draw(bool puntos, bool alambre, bool solido);
};