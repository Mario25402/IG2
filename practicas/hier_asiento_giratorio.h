#include "cilindro.h"
#include "hier_asiento.h"

class AsientoGiratorio{
    private:
        Asiento *asiento;
        Cilindro *cilindro;

    public:
        AsientoGiratorio();
        void draw(bool puntos, bool alambre, bool solido);
};