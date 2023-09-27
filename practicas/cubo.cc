#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
   //float dist = lado / 2.0f;
   //v.resize(8);

   // Vertices frontales
   /*v[0] = Tupla3f(-dist, 0, -dist);
   v[1] = Tupla3f(dist, 0, -dist);
   v[2] = Tupla3f(dist, lado, -dist);
   v[3] = Tupla3f(-dist, lado, -dist);

   // Vertices traseros
   v[4] = Tupla3f(-dist, 0, dist);
   v[5] = Tupla3f(dist, 0, dist);
   v[6] = Tupla3f(dist, lado, dist);
   v[7] = Tupla3f(-dist, lado, dist);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   
   // Frontal
   f[0] = Tupla3i(0,1,3);
   f[1] = Tupla3i(1,2,3);

   // Derecha
   f[2] = Tupla3i(1,5,6);
   f[3] = Tupla3i(1,6,2);

   // Trasera
   f[4] = Tupla3i(4,5,6);
   f[5] = Tupla3i(4,6,7);

   // Izquierda
   f[6] = Tupla3i(0,4,3);
   f[7] = Tupla3i(4,7,3);

   // Superior
   f[8] = Tupla3i(3,2,6);
   f[9] = Tupla3i(3,6,7);

   // Inferior
   f[10] = Tupla3i(4,0,1);
   f[11] = Tupla3i(4,1,5);

   /**********************************************/

   v.resize(8);

   // Vertices frontales
   v[0] = Tupla3f(-lado, -lado, -lado);
   v[1] = Tupla3f(-lado, -lado, lado);
   v[2] = Tupla3f(-lado, lado, -lado);
   v[3] = Tupla3f(-lado, lado, lado);

   // Vertices traseros
   v[4] = Tupla3f(lado, -lado, -lado);
   v[5] = Tupla3f(lado, -lado, lado);
   v[6] = Tupla3f(lado, lado, -lado);
   v[7] = Tupla3f(lado, lado, lado);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   
   // Frontal
   f[0] = Tupla3i(0,2,4);
   f[1] = Tupla3i(4,2,6);

   // Derecha
   f[2] = Tupla3i(1,5,3);
   f[3] = Tupla3i(3,5,7);

   // Trasera
   f[4] = Tupla3i(1,3,0);
   f[5] = Tupla3i(0,3,2);

   // Izquierda
   f[6] = Tupla3i(5,4,7);
   f[7] = Tupla3i(7,4,6);

   // Superior
   f[8] = Tupla3i(1,0,5);
   f[9] = Tupla3i(5,0,4);

   // Inferior
   f[10] = Tupla3i(3,7,2);
   f[11] = Tupla3i(2,7,6);
}