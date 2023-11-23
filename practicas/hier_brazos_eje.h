#include "hier_brazo.h"
#include "hier_eje.h"

class BrazosEje{
    private:
        Brazo *brazo;
        Eje *eje;
    
    public:
        BrazosEje();
        void draw(bool puntos, bool alambre, bool solido);
};