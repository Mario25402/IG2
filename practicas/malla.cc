#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla

void Malla3D::draw(bool puntos, bool alambre, bool solido)
{
   // Modo de visualización //

   setColor(puntos, alambre, solido);

   // Colores //

   if (id_vbo_c == 0)
      id_vbo_c = CrearVBO(GL_ARRAY_BUFFER, 3 * c.size() * sizeof(float), c.data());

   if (id_vbo_c != 0){
      // activar buffer: VBO de colores
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_c );
      // usar como buffer de colores el actualmente activo
      glColorPointer ( 3 , GL_FLOAT , 0 , 0 );
      // deactivar buffer: VBO de colores.
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      // habilitar el uso de tabla de colores
      glEnableClientState ( GL_COLOR_ARRAY );
   }

   // Vertices //

   if (id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3 * v.size() * sizeof(float), v.data());

   if (id_vbo_ver != 0){
      // activar buffer: VBO de vértices
      glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );
      // usar como buffer de vertices el actualmente activo
      glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
      // deactivar buffer: VBO de vértices.
      glBindBuffer ( GL_ARRAY_BUFFER , 0 );
      // habilitar el uso de tabla de vértices
      glEnableClientState ( GL_VERTEX_ARRAY );
   }

   // Triángulos //

   if (id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * f.size() * sizeof(int), f.data());

   if (id_vbo_tri != 0){
      // activar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );
      // dibujar con el buffer de índices activo
      glDrawElements (GL_TRIANGLES , 3 * f.size () , GL_UNSIGNED_INT , 0);
      // desactivar buffer: VBO de triángulos
      glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
      // desactivar uso de array de vértices
      glDisableClientState ( GL_VERTEX_ARRAY );
      glDisableClientState (GL_COLOR_ARRAY);
   }
}

// ************************************************************************* //

GLuint Malla3D::CrearVBO (GLuint tipo_vbo, GLuint tam, GLvoid * puntero_ram)
{
   GLuint id_vbo ; // resultado: identificador de VBO
   glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador
   glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData ( tipo_vbo , tam , puntero_ram , GL_STATIC_DRAW );

   glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
   return id_vbo ; // devolver el identificador resultado
}

// ************************************************************************* //

void Malla3D::setColor(bool puntos, bool alambre, bool solido)
{
   if (puntos and !oldPuntos){ // Si ha de pintarse como puntos y anteriormente no estaba activado
      glPointSize(5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      
      for (int i = 0; i < v.size(); i++)
         c[i] = Tupla3f(0.41f, 0.41f, 0.41f);

      id_vbo_c = 0; // actualizar el VBO de colores
   }
   
   if (alambre and !oldAlambre){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      for (int i = 0; i < v.size(); i++)
         c[i] = Tupla3f(0.0f, 0.0f, 0.0f);

      id_vbo_c = 0;
   }

   if (solido and !oldSolido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      for (int i = 0; i < v.size(); i++)
         c[i] = Tupla3f(0.0f, 0.5f, 0.5f);

      id_vbo_c = 0;
   }

   // actualizar los estados anteriores
   oldPuntos = puntos;
   oldAlambre = alambre;
   oldSolido = solido;
}

// ************************************************************************* //

void Malla3D::calcularNormales()
{
   nv.resize(v.size());
   Tupla3f normal_vertice(0,0,0);

   for (int i = 0; i < f.size(); i++){
      float p = f[i][0]; // Índice del vértice 0 de la cara i
      float q = f[i][1]; // Índice del vértice 1 de la cara i
      float r = f[i][2]; // Índice del vértice 2 de la cara i

      Tupla3f a = v[q] - v[p];
      Tupla3f b = v[r] - v[p];

      Tupla3f normal_cara = a.cross(b);

      // Si la normal de la cara i no vale cero, normalizarla
      if (normal_vertice.lengthSq() != 0)
         normal_vertice = normal_vertice.normalized(); // Normal de la cara i
      else 
         normal_vertice = normal_cara;     

      nv[p] = nv[p] + normal_vertice; // Sumar la normal de la cara i al vértice p
      nv[q] = nv[q] + normal_vertice; // Sumar la normal de la cara i al vértice q
      nv[r] = nv[r] + normal_vertice; // Sumar la normal de la cara i al vértice r
   }

   // Normalizar los vectores normales
   std::cout << "Tamaño: " << nv.size() << std::endl;
   for (int i = 0; i < nv.size(); i++){
      nv[i] = nv[i].normalized(); std::cout << i << std::endl;}
}

// ************************************************************************* //

void Malla3D::setMaterial(Material *mat)
{
   mat->aplicar();
}