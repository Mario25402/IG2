#include "auxiliar.h"
#include "malla.h"
#include "piramidepentagonal.h"

PiramidePentagonal::PiramidePentagonal(float h, float r)
{
   // inicializar la tabla de vértices
   v.resize(14);
   c.resize(v.size());
   

   // Vertices inferiores
   v[0] = Tupla3f(r * cos(240 * (M_PI/180)), 0, r * sin(240 * (M_PI/180)));
   v[1] = Tupla3f(r * cos(300 * (M_PI/180)), 0, r * sin(300 * (M_PI/180)));
   v[2] = Tupla3f(r * cos(0 * (M_PI/180)), 0, r * sin(0 * (M_PI/180)));
   v[3] = Tupla3f(r * cos(60 * (M_PI/180)), 0, r * sin(60 * (M_PI/180)));
   v[4] = Tupla3f(r * cos(120 * (M_PI/180)), 0, r * sin(120 * (M_PI/180)));
   v[5] = Tupla3f(r * cos(180 * (M_PI/180)), 0, r * sin(180 * (M_PI/180)));

   // Vertices superiores
   v[6] = Tupla3f((r / 2.0f) * cos(240 * (M_PI/180)), h, (r / 2.0f) * sin(240 * (M_PI/180)));
   v[7] = Tupla3f((r / 2.0f) * cos(300 * (M_PI/180)), h, (r / 2.0f) * sin(300 * (M_PI/180)));
   v[8] = Tupla3f((r / 2.0f) * cos(0 * (M_PI/180)), h, (r / 2.0f) * sin(0 * (M_PI/180)));
   v[9] = Tupla3f((r / 2.0f) * cos(60 * (M_PI/180)), h, (r / 2.0f) * sin(60 * (M_PI/180)));
   v[10] = Tupla3f((r / 2.0f) * cos(120 * (M_PI/180)), h, (r / 2.0f) * sin(120 * (M_PI/180)));
   v[11] = Tupla3f((r / 2.0f) * cos(180 * (M_PI/180)), h, (r / 2.0f) * sin(180 * (M_PI/180)));

   // Vertices centrales
   v[12] = Tupla3f(0,h,0);  // superior
   v[13] = Tupla3f(0,0,0);  // inferior
        
   /********************************************/
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   f.resize(24);

   // Trasera central
   f[0] = Tupla3i(0,7,1);
   f[1] = Tupla3i(0,6,7);

   // Trasera derecha
   f[2] = Tupla3i(1,7,2);
   f[3] = Tupla3i(2,7,8);

   // Frontal derecha
   f[4] = Tupla3i(3,2,9);
   f[5] = Tupla3i(9,2,8);

   // Frontal central
   f[6] = Tupla3i(4,3,9);
   f[7] = Tupla3i(4,9,10);

   // Frontal izquierda
   f[8] = Tupla3i(5,4,11);
   f[9] = Tupla3i(4,10,11);

   // Trasera izquierda
   f[10] = Tupla3i(0,5,11);
   f[11] = Tupla3i(0,11,6);

   // Base inferior
   f[12] = Tupla3i(1,13,0);
   f[13] = Tupla3i(2,13,1);
   f[14] = Tupla3i(3,13,2);
   f[15] = Tupla3i(4,13,3);
   f[16] = Tupla3i(5,13,4);
   f[17] = Tupla3i(0,13,5);

   // Base superior
   f[18] = Tupla3i(6,12,7);
   f[19] = Tupla3i(7,12,8);
   f[20] = Tupla3i(8,12,9);
   f[21] = Tupla3i(9,12,10);
   f[22] = Tupla3i(10,12,11);
   f[23] = Tupla3i(11,12,6);

   /********************************************/
   
   calcularNormales();
}

