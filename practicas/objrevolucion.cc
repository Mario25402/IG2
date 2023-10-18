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
   //ply::read_vertices(archivo, v);
   ply::read(archivo, v, f);

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

   int M = archivo.size();
   int N = num_instancias;

   // añadir tapa inferior
   if (tapa_inf)
      v.push_back(polo_sur);

   else{
      float coordY = v.front()[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo sur
   }

   /*for (int i = 0; i < N; i++){
      f.push_back(Tupla3i(i*M, ((i*M)+M) % (M*N), v.size()-1));
   }*/

   // añadir tapa superior
   if (tapa_sup)
      v.push_back(polo_norte);

   else{
      float coordY = v.at(v.size()-2)[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo norte
   }

   /* for (int i = 1; i <= N; i++){
      f.push_back(Tupla3i((i*M)-1, ((i*M)+M-1) % (M*N), v.size()-1));
   } */
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

   // añadir tapa inferior
   if (tapa_inf){
      int M = archivo.size();
      int N = num_instancias;

      v.push_back(polo_sur);

      for (int i = 0; i < N; i++){
         f.push_back(Tupla3i(i*M, ((i*M)+M) % (M*N), v.size()-1));
      }
   }
   /*else{
      float coordY = v.front()[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo sur
   }*/

   // añadir tapa superior
   if (tapa_sup){
      int M = archivo.size();
      int N = num_instancias;

      v.push_back(polo_norte);

      for (int i = 1; i <= N; i++){
         f.push_back(Tupla3i((i*M)-1, ((i*M)+M-1) % (M*N), v.size()-1));
      }
   }
   /*else{
      float coordY = v.back()[1];
      v.push_back(Tupla3f(0.0f, coordY, 0.0f)); // añadir polo norte
   }*/
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

   if (v.front()[1] > v.back()[1]){
      std::reverse(v.begin(), v.end());
   }

   c.resize(v.size());
   f.clear();
   for (int i = 0; i < N; i++){
      for (int j = 0; j < M-1; j++){
         int a = M * i + j;
         int b = M * ((i+1) % N) + j;

         f.push_back(Tupla3i(a, b+1, b));    // (a, b, b+1)
         f.push_back(Tupla3i(a, a+1, b+1));  // (a, b+1, a+1)
      }
   }
}
