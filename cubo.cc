#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   float dist = lado / 2.0f;
   // inicializar la tabla de vértices
   v.resize(8);

   v[0] = Tupla3f(-dist, 0, -dist);
   v[1] = Tupla3f(dist, 0, -dist);
   v[2] = Tupla3f(dist, lado, -dist);
   v[3] = Tupla3f(-dist, lado, -dist);

   v[4] = Tupla3f(-dist, 0, dist);
   v[5] = Tupla3f(dist, 0, dist);
   v[6] = Tupla3f(dist, lado, dist);
   v[7] = Tupla3f(-dist, lado, dist);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   
   f[0] = Tupla3i(0,1,3);
   f[1] = Tupla3i(1,2,3);

   f[2] = Tupla3i(1,5,6);
   f[3] = Tupla3i(1,6,2);

   f[4] = Tupla3i(4,5,6);
   f[5] = Tupla3i(4,6,7);

   f[6] = Tupla3i(0,4,3);
   f[7] = Tupla3i(4,7,3);

   f[8] = Tupla3i(3,2,6);
   f[9] = Tupla3i(3,6,7);

   f[10] = Tupla3i(4,0,1);
   f[11] = Tupla3i(4,1,5);

}