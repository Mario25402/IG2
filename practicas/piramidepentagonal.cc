#include "auxiliar.h"
#include "malla.h"
#include "piramidepentagonal.h"

PiramidePentagonal::PiramidePentagonal(float h, float r)
{
   // inicializar la tabla de vértices
   v.resize(14);

   // Vertices inferiores
   v[0] = Tupla3f(r * cos(0), 0, r * sin(0));
   v[1] = Tupla3f(r * cos(60), 0, r * sin(60));
   v[2] = Tupla3f(r * cos(120), 0, r * sin(120));
   v[3] = Tupla3f(r * cos(180), 0, r * sin(180));
   v[4] = Tupla3f(r * cos(240), 0, r * sin(240));
   v[5] = Tupla3f(r * cos(300), 0, r * sin(300));

   // Vertices superiores
   v[6] = Tupla3f((r / 2.0f) * cos(0), h / 2.0f, (r / 2.0f) * sin(0));
   v[7] = Tupla3f((r / 2.0f) * cos(60), h / 2.0f, (r / 2.0f) * sin(60));
   v[8] = Tupla3f((r / 2.0f) * cos(120), h / 2.0f, (r / 2.0f) * sin(120));
   v[9] = Tupla3f((r / 2.0f) * cos(180), h / 2.0f, (r / 2.0f) * sin(180));
   v[10] = Tupla3f((r / 2.0f) * cos(240), h / 2.0f, (r / 2.0f) * sin(240));
   v[11] = Tupla3f((r / 2.0f) * cos(300), h / 2.0f, (r / 2.0f) * sin(300));

   // Vertices centrales
   v[12] = Tupla3f(0, h / 2.0f,0);  // superior
   v[13] = Tupla3f(0,0,0);          // inferior
        
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(24);

   // Frontal central
   f[0] = Tupla3i(0,1,6);
   f[1] = Tupla3i(1,7,6);

   // Frontal derecha
   f[2] = Tupla3i(1,2,7);
   f[3] = Tupla3i(1,8,7);

   // Trasera derecha
   f[4] = Tupla3i(3,2,8);
   f[5] = Tupla3i(3,8,9);

   // Trasera central
   f[6] = Tupla3i(4,3,10);
   f[7] = Tupla3i(3,9,10);

   // Trasera izquierda
   f[8] = Tupla3i(5,4,10);
   f[9] = Tupla3i(4,10,11);

   // Frontal izquierda
   f[10] = Tupla3i(5,0,6);
   f[11] = Tupla3i(5,6,11);

   // Base superior
   f[12] = Tupla3i(6,7,12);
   f[13] = Tupla3i(7,8,12);
   f[14] = Tupla3i(8,9,12);
   f[15] = Tupla3i(9,10,12);
   f[16] = Tupla3i(10,11,12);
   f[17] = Tupla3i(11,6,12);

   // Base inferior
   f[18] = Tupla3i(0,1,13);
   f[19] = Tupla3i(1,2,13);
   f[20] = Tupla3i(2,3,13);
   f[21] = Tupla3i(3,4,13);
   f[22] = Tupla3i(4,5,13);
   f[23] = Tupla3i(5,0,13);

   // inicializar la/s tabla/s de colores
   
}

