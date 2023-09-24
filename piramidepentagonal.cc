#include "auxiliar.h"
#include "malla.h"
#include "piramidepentagonal.h"

PiramidePentagonal::PiramidePentagonal(float h, float r)
{

   // inicializar la tabla de vértices
   v.resize(12);

   v[0] = Tupla3f(r * cos(0), h / 2.0f, r * sin(0));
   v[1] = Tupla3f(r * cos(60), h / 2.0f, r * sin(60));
   v[2] = Tupla3f(r * cos(120), h / 2.0f, r * sin(120));
   v[3] = Tupla3f(r * cos(180), h / 2.0f, r * sin(180));
   v[4] = Tupla3f(r * cos(240), h / 2.0f, r * sin(240));
   v[5] = Tupla3f(r * cos(300), h / 2.0f, r * sin(300));

   v[6] = Tupla3f(r * cos(0), h / 4.0f, r * sin(0));
   v[7] = Tupla3f(r * cos(60), h / 4.0f, r * sin(60));
   v[8] = Tupla3f(r * cos(120), h / 4.0f, r * sin(120));
   v[9] = Tupla3f(r * cos(180), h / 4.0f, r * sin(180));
   v[10] = Tupla3f(r * cos(240), h / 4.0f, r * sin(240));
   v[11] = Tupla3f(r * cos(300), h / 4.0f, r * sin(300));
        
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(20);

   f[0] = Tupla3i(0,1,6);
   f[1] = Tupla3i(1,7,6);

   f[2] = Tupla3i(1,2,7);
   f[3] = Tupla3i(1,8,7);

   f[4] = Tupla3i(3,2,8);
   f[5] = Tupla3i(3,8,9);

   f[6] = Tupla3i(4,3,10);
   f[7] = Tupla3i(3,9,10);

   f[8] = Tupla3i(5,4,10);
   f[9] = Tupla3i(4,10,11);

   f[10] = Tupla3i(5,0,6);
   f[11] = Tupla3i(5,6,11);

   f[12] = Tupla3i(0,1,3);
   f[13] = Tupla3i(1,2,3);
   f[14] = Tupla3i(0,3,4);
   f[15] = Tupla3i(0,4,5);

   f[16] = Tupla3i(6,7,10);
   f[17] = Tupla3i(7,8,9);
   f[18] = Tupla3i(7,9,10);
   f[19] = Tupla3i(6,10,11);

   /*
   f[12] = Tupla3i();
   f[13] = Tupla3i();
   f[14] = Tupla3i();
   f[15] = Tupla3i();
   f[16] = Tupla3i();
   f[17] = Tupla3i();

   f[18] = Tupla3i();
   f[19] = Tupla3i();
   f[20] = Tupla3i();
   f[21] = Tupla3i();
   f[22] = Tupla3i();
   f[23] = Tupla3i();
   */

   // inicializar la/s tabla/s de colores
   
}

