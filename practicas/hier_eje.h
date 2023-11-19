#include "cilindro.h"

class Eje{
    private:
        Cilindro *cilindro;
    
    public:
        Eje();
        void draw(bool puntos, bool alambre, bool solido);
};