#include "auxiliar.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <algorithm>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf)
{
   // leer datos del archivo PLY
   //ply::read_vertices(archivo, v);
   ply::read(archivo, v, f);

   // rellenar en orden ascendente en el eje Y
   if (v.front()[1] > v.back()[1]){
      std::reverse(v.begin(), v.end());
   }

   /////

   Tupla3f polo_sur, polo_norte;

   // Comprobar si no hay polo sur
   if (!tapa_sup){
      polo_sur = v.back();
      tapa_sup = (polo_sur[0] == 0.0f and polo_sur[2] == 0.0f);

      // eliminar polo sur
      if (tapa_sup) v.erase(v.begin());
   }

   // Comprobar si no hay polo norte
   if (!tapa_sup){
      polo_norte = v.back();
      tapa_sup = (polo_norte[0] == 0.0f and polo_norte[2] == 0.0f);

      // eliminar polo norte
      if (tapa_sup) v.pop_back();
   }

   /////
   
   crearMalla(v, num_instancias);

   /////

   // añadir vertice de la tapa inferior
   if (tapa_inf)
      v.push_back(polo_sur);

   else{
      float coordY = v.front()[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo sur
   }

   // añadir vertice de la tapa superior
   if (tapa_sup)
      v.push_back(polo_norte);

   else{
      float coordY = v.at(v.size()-2)[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo norte
   }

   /////

   c.resize(v.size());
   int N = num_instancias;
   int M = v.size() / N; // inicio o fin de la fila en la malla

   // añadir caras de la tapas
   for (int i = 0; i < N; i++){
      f.push_back(Tupla3i(v.size()-2, i*M, ((i*M)+M) % (M*N)));               // inferior
      f.push_back(Tupla3i(((i+1)*M)-1, v.size()-1, (((i+1)*M)+M-1) % (M*N))); // superior
   }
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) 
{
   for (int i = 0; i < archivo.size(); i++)
      v.push_back(archivo[i]);

   /////

   int num_vertices = v.size();
   Tupla3f polo_sur, polo_norte;

   // eliminar polo sur
   if (tapa_inf){
      polo_sur = v[0];
      v.erase(v.begin());
      num_vertices--;
   }
   
   // eliminar polo norte
   if (tapa_sup){
      polo_norte = v[num_vertices-1];
      v.pop_back();
      num_vertices--;
   }

   /////
   
   crearMalla(v, num_instancias);

   /////

   // añadir vertice de la tapa inferior
   if (tapa_inf)
      v.push_back(polo_sur);

   else{
      float coordY = v.front()[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo sur
   }

   // añadir vertice de la tapa superior
   if (tapa_sup)
      v.push_back(polo_norte);

   else{
      float coordY = v.at(v.size()-2)[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo norte
   }

   /////

   int N = num_instancias;
   int M = v.size() / N; // inicio o fin de la fila en la malla

   // añadir caras de la tapas
   for (int i = 0; i < N; i++){
      f.push_back(Tupla3i(v.size()-2, i*M, ((i*M)+M) % (M*N)));               // inferior
      f.push_back(Tupla3i(((i+1)*M)-1, v.size()-1, (((i+1)*M)+M-1) % (M*N))); // superior
   }
}

// *****************************************************************************
// crea la malla de revolución dado un perfil

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) 
{
   int N = num_instancias;
   int M = perfil_original.size();

   v.clear();
   for (int i = 0; i < N; i++){
      for (int j = 0; j < M; j++){
         float x = perfil_original[j][0] * cos(2.0f*M_PI*i/N);
         float y = perfil_original[j][1];
         float z = perfil_original[j][0] * sin(2.0f*M_PI*i/N);

         v.push_back(Tupla3f(x,y,z));
      }
   }

   c.resize(v.size());
   f.clear();
   for (int i = 0; i < N; i++){
      for (int j = 0; j < M-1; j++){
         int a = M * i + j;
         int b = M * ((i+1) % N) + j;

         f.push_back(Tupla3i(a, b+1, b));    // f.push_back(Tupla3i((a, b, b+1));
         f.push_back(Tupla3i(a, a+1, b+1));  // f.push_back(Tupla3i((a, b+1, a+1));
      }
   }
}

// *****************************************************************************

float ObjRevolucion::centrar()
{
   float min = INFINITY;

   for (int i = 0; i < v.size(); i++){
      if (v[i][1] < min)
         min = v[i][1];   
   }

   return min;
}
