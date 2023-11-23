// #############################################################################
//
// Informática Gráfica D (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
public:
   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw(bool puntos, bool alambre, bool solido, int color);

   // función que fija el material del objeto
   void setMaterial (Material *mat);

   // función que calcula las normales del objeto
   void calcularNormales();

protected:
   std::vector<Tupla3f> v;  // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f;  // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c;  // tabla de colores
   std::vector<Tupla3f> nv; // tabla de normales de vértices

private:
   GLuint id_vbo_ver = 0;  // variables que controlan
   GLuint id_vbo_tri = 0;  // si un VBO ha sido creado
   GLuint id_vbo_c   = 0;  // o no, además de identificarlo

   bool oldPuntos = false;    // variables que controlan que no
   bool oldAlambre = false;   // se rellenen de nuevo 
   bool oldSolido = false;    // los colores innecesariamente

   // función que crea un VBO
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);

   // función que cambia el color de los objetos según el modo de dibujado
   void setColor(bool puntos, bool alambre, bool solido, int color);
};

#endif
