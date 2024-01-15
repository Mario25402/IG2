#include "cilindro.h"

class Eje{
    private:
        Cilindro *cilindro;
    
    public:
        Eje();

        void draw(bool puntos, bool alambre, bool solido);

        void setTextura();
        void setMaterial(Material *mat);
        void setSeleccionado(bool seleccionado);
};