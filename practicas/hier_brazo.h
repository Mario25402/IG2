#include "cubo.h"
#include "cilindro.h"

class Brazo{
    private:
        Cubo *cubo;
        Cilindro *cilindro;

    public:
        Brazo();
        void draw(bool puntos, bool alambre, bool solido);
};