#include "auxiliar.h"
#include "malla.h"

// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,

void Malla3D::draw(bool puntos, bool alambre, bool solido)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
   // activar buffer: VBO de vértices
   
   GLuint id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data());
   GLuint id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(int), f.data());
   //GLuint id_vbo_col = CrearVBO();

   /* if (puntos) draw_puntos();
   if (alambre) draw_alambre();
   if (solido) draw_solido(); */

   // activar buffer: VBO de vértices
   glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );
   // usar como buffer de vertices el actualmente activo
   glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
   // deactivar buffer: VBO de vértices.
   glBindBuffer ( GL_ARRAY_BUFFER , 0 );
   // habilitar el uso de tabla de vértices
   glEnableClientState ( GL_VERTEX_ARRAY );
   //
   // activar buffer: VBO de triángulos
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );
   // dibujar con el buffer de índices activo
   glDrawElements ( GL_TRIANGLES , 3* f . size () , GL_UNSIGNED_INT , 0 ) ;
   // desactivar buffer: VBO de triángulos
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
   // desactivar uso de array de vértices
   glDisableClientState ( GL_VERTEX_ARRAY );
}

void Malla3D::draw_puntos()
{
  
}

void Malla3D::draw_alambre()
{

}

void Malla3D::draw_solido()
{

}

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

void Malla3D::setColor()
{

}