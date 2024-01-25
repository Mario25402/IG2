#include "tetraedro.h"

Tetraedro::Tetraedro(float l){
    v.resize(4);
    v[2] = {0, 0, l/2};
    v[0] = {0, l, 0};
    v[1] = {-l/2, 0, -l/2};
    v[3] = {l/2, 0, -l/2};

    f.resize(4);
    f[0] = {0, 1, 2};
    f[1] = {0, 2, 3};
    f[2] = {0, 3, 1};
    f[3] = {1, 3, 2};

    c.resize(v.size(), {0, 1, 1});
}