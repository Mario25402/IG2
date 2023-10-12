#include "auxiliar.h"
#include "objrevolucion.h"
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   ply::read(archivo, v, f);

   /////

   Tupla3f inicio = v[0];

   if (inicio[1] == 0.0f)
      tapa_inf = true;

   /////

   Tupla3f fin = v[v.size()-1];

   if (fin[1] == 0.0f)
      tapa_sup = true;

   /////


}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   /*for (int i = 0; i < archivo.size(); i++){
      v.push_back(archivo[i]);
   }*/
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int M = perfil_original.size();
   int N = num_instancias;

   float salto = 2.0f * M_PI / (float)N;
   int cont = 0;

   v.clear();
   v.resize(N*perfil_original.size());
   c.resize(v.size());

   for (unsigned long long i = 0; i < N; ++i){
      for (unsigned long j = 0; j < perfil_original.size(); ++j){
         float x = cos(i*salto) * perfil_original[j][0];
         float y = perfil_original[j][1];
         float z = -sin(i*salto)*perfil_original[j][0];

         v[cont] = Tupla3f(x,y,z);
         cont++;
      }
   }

   long n = v.size();
   long m = n/N;

   f.resize((m-1)*n*2);
   cont = 0;

   for (long fil = 0; fil < (m-1); ++fil){
      for (long col = 0; col < n; ++col){
         long x=col%n;
         long y=(col+m)%n;
         long z=(col+1)%n;

         f[cont] = Tupla3i(x,y,z);
         cont++;         

         x = (x+m)%n;
         y = (y+1)%n;

         f[cont] = Tupla3i(x,y,z);
         cont++;
      }
   }
}
