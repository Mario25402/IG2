#include "flecha.h"

class EjesFlechas : public Flecha3D
{
    private:
        Flecha3D *fx = nullptr;
        Flecha3D *fy = nullptr;
        Flecha3D *fz = nullptr;

        Material *mx = nullptr;
        Material *my = nullptr;
        Material *mz = nullptr;
    
    public:
        EjesFlechas();
        void draw(bool puntos, bool alambre, bool solido, int color);
};