#include "cuadro.h"

Cuadro::Cuadro(float l){
    v.resize(4);
    v[0] = Tupla3f(-l, -l/2.0f, 0); // Abajo izquierda
    v[1] = Tupla3f(l, -l/2.0f, 0);  // Abajo derecha
    v[2] = Tupla3f(l, l/2.0f, 0);   // Arriba derecha
    v[3] = Tupla3f(-l, l/2.0f, 0);  // Arriba izquierda

    f.resize(2);
    f[0] = Tupla3i(0,1,2);
    f[1] = Tupla3i(0,2,3);

    c.resize(v.size());
    c[0] = Tupla3f(1,1,1);
    c[1] = Tupla3f(1,1,1);
    c[2] = Tupla3f(1,1,1);
    c[3] = Tupla3f(1,1,1);

    ct.resize(v.size());
    ct[0] = Tupla2f(0,1);
    ct[1] = Tupla2f(1,1);
    ct[2] = Tupla2f(1,0);
    ct[3] = Tupla2f(0,0);

    calcularNormales();
}