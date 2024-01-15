#include "cilindro.h"
#include "hier_asiento.h"

class AsientoGiratorio{
    private:
        Asiento *asiento;
        Cilindro *cilindro;

    public:
        AsientoGiratorio();

        void animar(float velAnimacion);
        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setVelocidad(float despBarra);
        void setSeleccionado(bool seleccionado);
};