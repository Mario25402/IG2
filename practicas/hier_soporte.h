#include "hier_pie.h"

class Soporte{
    private:
        Pie *pie;
        Cubo *cubo;

    public:
        Soporte();
        void draw(bool puntos, bool alambre, bool solido);
};