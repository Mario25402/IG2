#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
   v.resize(8);

   // Vertices inferiores
   v[0] = Tupla3f(-lado/2.0f, -lado/2.0f, lado/2.0f);
   v[1] = Tupla3f(lado/2.0f, -lado/2.0f, lado/2.0f);
   v[2] = Tupla3f(lado/2.0f, -lado/2.0f, -lado/2.0f);
   v[3] = Tupla3f(-lado/2.0f, -lado/2.0f, -lado/2.0f);

   // Vertices superiores
   v[4] = Tupla3f(-lado/2.0f, lado/2.0f, lado/2.0f);
   v[5] = Tupla3f(lado/2.0f, lado/2.0f, lado/2.0f);
   v[6] = Tupla3f(lado/2.0f, lado/2.0f, -lado/2.0f);
   v[7] = Tupla3f(-lado/2.0f, lado/2.0f, -lado/2.0f);

   /*v[0]=Tupla3f(-lado/2,lado/2,-lado/2);
   v[1]=Tupla3f(lado/2,lado/2,-lado/2);
   v[2]=Tupla3f(lado/2,-lado/2,-lado/2);
   v[3]=Tupla3f(-lado/2,-lado/2,-lado/2);
   v[4]=Tupla3f(-lado/2,lado/2,lado/2);
   v[5]=Tupla3f(lado/2,lado/2,lado/2);
   v[6]=Tupla3f(lado/2,-lado/2,lado/2);
   v[7]=Tupla3f(-lado/2,-lado/2,lado/2);*/

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
   f[4] = Tupla3i(2,6,3);
   f[5] = Tupla3i(3,6,7);

   // Izquierda
   f[6] = Tupla3i(0,3,4);
   f[7] = Tupla3i(4,3,7);

   // Inferior
   f[8] = Tupla3i(1,0,3);
   f[9] = Tupla3i(1,3,2);

   // Superior
   f[10] = Tupla3i(4,5,6);
   f[11] = Tupla3i(4,6,7);

   /*f[0]=Tupla3i(4,1,0);
   f[1]=Tupla3i(1,4,5);
   f[2]=Tupla3i(5,2,1);
   f[3]=Tupla3i(2,5,6);
   f[4]=Tupla3i(7,2,6);
   f[5]=Tupla3i(2,7,3);
   f[6]=Tupla3i(0,7,4);
   f[7]=Tupla3i(7,0,3);
   f[8]=Tupla3i(5,7,6);
   f[9]=Tupla3i(7,5,4);
   f[10]=Tupla3i(3,1,2);
   f[11]=Tupla3i(1,3,0);*/

   /********************************************/
   // inicializar la/s tabla/s de colores
   c.resize(v.size());

   for (int i = 0; i < c.size(); i++){
      c[i] = Tupla3f(1.0f, 1.0f, 1.0f);
   }
}