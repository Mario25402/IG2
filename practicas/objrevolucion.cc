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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool textura)
{
   // leer datos del archivo PLY
   ply::read_vertices(archivo, v);

   // rellenar en orden ascendente en el eje Y
   if (v.front()[1] > v.back()[1])
      std::reverse(v.begin(), v.end());
   
   /////

   Tupla3f polo_sur, polo_norte;
   bool tapa_inf = false;
   bool tapa_sup = false;

   // Comprobar si hay polo sur
   polo_sur = v.front();
   tapa_inf = (polo_sur[0] <= LIM_TAPAS and polo_sur[2] <= LIM_TAPAS);

   // eliminar polo sur
   if (tapa_inf) v.erase(v.begin());

   // Comprobar si hay polo norte
   polo_norte = v.back();
   tapa_sup = (polo_norte[0] <= LIM_TAPAS and polo_norte[2] <= LIM_TAPAS);

   // eliminar polo norte
   if (tapa_sup) v.pop_back();

   /////
   
   crearMalla(v, num_instancias);

   /////

   // añadir vertice de la tapa inferior
   if (tapa_inf)
      v.push_back(polo_sur);

   // añadir vertice de la tapa superior
   if (tapa_sup)
      v.push_back(polo_norte);

   /////

   if (tapa_inf or tapa_sup){
      c.resize(v.size());
      int N = num_instancias;
      int M = v.size() / N; // inicio o fin de la fila en la malla

      // determinar posición del polo sur en el vector de vértices
      int pos_polo;
      if (tapa_inf and tapa_sup) pos_polo = v.size()-2;
      else if (tapa_inf) pos_polo = v.size()-1;

      // añadir caras de la tapas
      for (int i = 0; i < N; i++){
         if (tapa_inf)
            f.push_back(Tupla3i(pos_polo, ((i*M)+M) % (M*N), i*M));

         if (tapa_sup)
            f.push_back(Tupla3i(v.size()-1, ((i+1)*M)-1, (((i+1)*M)+M-1) % (M*N)));
      }
   }

   calcularNormales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool textura) 
{
   // rellenar el vector de vertices
   for (int i = 0; i < archivo.size(); i++)
      v.push_back(archivo[i]);

   // rellenar en orden ascendente en el eje Y
   if (v.front()[1] > v.back()[1]){
      std::reverse(v.begin(), v.end());
   }

   /////

   Tupla3f polo_sur, polo_norte;
   bool tapa_inf = false;
   bool tapa_sup = false;

   // Comprobar si hay polo sur
   polo_sur = v.front();
   tapa_inf = (polo_sur[0] <= LIM_TAPAS and polo_sur[2] <= LIM_TAPAS);

   // eliminar polo sur
   if (tapa_inf) v.erase(v.begin());

   // Comprobar si hay polo norte
   polo_norte = v.back();
   tapa_sup = (polo_norte[0] <= LIM_TAPAS and polo_norte[2] <= LIM_TAPAS);

   // eliminar polo norte
   if (tapa_sup) v.pop_back();

   /////
   
   crearMalla(v, num_instancias);

   /////

   // añadir vertice de la tapa inferior
   if (tapa_inf)
      v.push_back(polo_sur);

   // añadir vertice de la tapa superior
   if (tapa_sup)
      v.push_back(polo_norte);

   /////

   if (tapa_inf or tapa_sup){
      c.resize(v.size());
      int N = num_instancias;
      int M = v.size() / N; // inicio o fin de la fila en la malla

      // determinar posición del polo sur en el vector de vértices
      int pos_polo = v.size()-1;
      if (tapa_inf and tapa_sup) pos_polo = v.size()-2;

      // añadir caras de la tapas
      for (int i = 0; i < N; i++){
         if (tapa_inf)
            f.push_back(Tupla3i(pos_polo, ((i*M)+M) % (M*N), i*M));

         if (tapa_sup)
            f.push_back(Tupla3i(v.size()-1, ((i+1)*M)-1, (((i+1)*M)+M-1) % (M*N)));
      }
   }

   calcularNormales();
}

// *****************************************************************************
// crea la malla de revolución dado un perfil

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool textura) 
{
   int N = num_instancias;
   int M = perfil_original.size();

   v.clear();
   for (int i = 0; i < N; i++){
      for (int j = 0; j < M; j++){
         float x = perfil_original[j][0] * cos(2.0f*M_PI*i/N) + 
                   perfil_original[j][2] * sin(2.0f*M_PI*i/N);

         float y = perfil_original[j][1];

         float z = perfil_original[j][0] * (-1 * sin(2.0f*M_PI*i/N)) + 
                   perfil_original[j][2] * cos(2.0f*M_PI*i/N);

         v.push_back(Tupla3f(x,y,z));
      }
   }

   c.resize(v.size());
   f.clear();

   for (int i = 0; i < N; i++){
      for (int j = 0; j < M-1; j++){
         int a = M * i + j;
         int b = M * ((i+1) % N) + j;

         f.push_back(Tupla3i(a,b,b+1));
         f.push_back(Tupla3i(a,b+1,a+1));
      }
   }
   
   if (textura) calcularTexturas();
    
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

// *****************************************************************************

void ObjRevolucion::calcularTexturas()
{
   ct.clear();
   int numVert = v.size();

   for (int i = 0; i < numVert; i++){           // Recorre los vertices de la malla
      Tupla3f normalizado = v[i].normalized(); // Normaliza el vertice (módulo 1)

      float phi = atan2(normalizado[2], normalizado[0]); // atan2(z,x) posicion en coordenadas esfericas
      float theta = acos(normalizado[1]);                // acos(y) posicion en coordenadas esfericas

      float s = 1.0f - (phi / (2.0f * M_PI));  // Eje X en la textura, normalizado entre 0 y 1
      float t = (theta / M_PI);                // Eje Y en la textura, normalizado entre 0 y 1

      ct.push_back(Tupla2f(s,t));   // Añade la coordenada de textura al vector
   }
}