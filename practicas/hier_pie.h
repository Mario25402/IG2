#include "cubo.h"
#include "piramidepentagonal.h"
#include "cilindro.h"

class Pie{
    private:    
        Cubo *cubo;
        PiramidePentagonal *piramide;

    public:
        Pie();
        void draw(bool puntos, bool alambre, bool solido);
};