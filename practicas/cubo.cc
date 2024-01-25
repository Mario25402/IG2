#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
   v.resize(8);

   // Vertices inferiores
   v[0] = Tupla3f(-lado/2.0f, 0, lado/2.0f);
   v[1] = Tupla3f(lado/2.0f, 0, lado/2.0f);
   v[2] = Tupla3f(lado/2.0f, 0, -lado/2.0f);
   v[3] = Tupla3f(-lado/2.0f, 0, -lado/2.0f);

   // Vertices superiores
   v[4] = Tupla3f(-lado/2.0f, lado, lado/2.0f);
   v[5] = Tupla3f(lado/2.0f, lado, lado/2.0f);
   v[6] = Tupla3f(lado/2.0f, lado, -lado/2.0f);
   v[7] = Tupla3f(-lado/2.0f, lado, -lado/2.0f);

   /********************************************/
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   
   // Frontal
   f[0] = Tupla3i(0,1,4);
   f[1] = Tupla3i(1,5,4);

   // Derecha
   f[2] = Tupla3i(1,2,6);
   f[3] = Tupla3i(1,6,5);

   // Trasera
   f[4] = Tupla3i(2,3,6);
   f[5] = Tupla3i(3,7,6);

   // Izquierda
   f[6] = Tupla3i(4,3,0);
   f[7] = Tupla3i(7,3,4);

   // Inferior
   f[8] = Tupla3i(1,0,3);
   f[9] = Tupla3i(1,3,2);

   // Superior
   f[10] = Tupla3i(4,5,6);
   f[11] = Tupla3i(4,6,7);

   /********************************************/

   c.resize(v.size(), Tupla3f(1,1,1));

   /********************************************/

   // Hacer inversion horizontal de coordenadas
   ct.resize(v.size());
   ct[0] = Tupla2f(0,1);
   ct[1] = Tupla2f(1,1);
   ct[2] = Tupla2f(0,1);
   ct[3] = Tupla2f(1,1);

   ct[4] = Tupla2f(0,0);
   ct[5] = Tupla2f(1,0);
   ct[6] = Tupla2f(0,0);
   ct[7] = Tupla2f(1,0);

   /********************************************/

   calcularNormales();
}

Cubo::Cubo(float l, float r, float g, float b){
      // inicializar la tabla de vértices
   v.resize(8);

   // Vertices inferiores
   v[0] = Tupla3f(-l/2.0f, 0, l/2.0f);
   v[1] = Tupla3f(l/2.0f, 0, l/2.0f);
   v[2] = Tupla3f(l/2.0f, 0, -l/2.0f);
   v[3] = Tupla3f(-l/2.0f, 0, -l/2.0f);

   // Vertices superiores
   v[4] = Tupla3f(-l/2.0f, l, l/2.0f);
   v[5] = Tupla3f(l/2.0f, l, l/2.0f);
   v[6] = Tupla3f(l/2.0f, l, -l/2.0f);
   v[7] = Tupla3f(-l/2.0f, l, -l/2.0f);

   /********************************************/
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(12);
   
   // Frontal
   f[0] = Tupla3i(0,1,4);
   f[1] = Tupla3i(1,5,4);

   // Derecha
   f[2] = Tupla3i(1,2,6);
   f[3] = Tupla3i(1,6,5);

   // Trasera
   f[4] = Tupla3i(2,3,6);
   f[5] = Tupla3i(3,7,6);

   // Izquierda
   f[6] = Tupla3i(4,3,0);
   f[7] = Tupla3i(7,3,4);

   // Inferior
   f[8] = Tupla3i(1,0,3);
   f[9] = Tupla3i(1,3,2);

   // Superior
   f[10] = Tupla3i(4,5,6);
   f[11] = Tupla3i(4,6,7);

   /********************************************/

   c.resize(v.size(), Tupla3f(r,g,b));

   /********************************************/

   // Hacer inversion horizontal de coordenadas
   ct.resize(v.size());
   ct[0] = Tupla2f(0,1);
   ct[1] = Tupla2f(1,1);
   ct[2] = Tupla2f(0,1);
   ct[3] = Tupla2f(1,1);

   ct[4] = Tupla2f(0,0);
   ct[5] = Tupla2f(1,0);
   ct[6] = Tupla2f(0,0);
   ct[7] = Tupla2f(1,0);
}