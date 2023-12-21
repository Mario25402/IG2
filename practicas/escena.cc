

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   /////

   init_objetos();
   init_luces();
   init_materiales();
}

//**************************************************************************
// funciones de animacion de cualquier tipo
//**************************************************************************

void Escena::animarModeloJerarquico()
{
   if (animacion)
      modelo->animar(velAnimacion);
}

void Escena::animarLuzPosicional()
{
   if (animacion and iluminado and luz1){
      luzPos->animarPosicion();
   }
}

void Escena::animarLuzDireccional(){
   if (animacion and iluminado and luz2){
      luzDir->animarColores();
   }
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

void Escena::init_objetos()
{
   cuadro = new Cuadro(100);
   esfera = new Esfera(20, 20, 50);
   modelo = new ModeloJerarquico();

   cuadro->setTextura("../texturas/text-mundo.jpg");
   //esfera->setTextura("../texturas/text-mundo.jpg");
}

void Escena::init_luces()
{
   angulo_alfa = 0;
   angulo_beta = 0;

   luzPos = new LuzPosicional({100,0,0}, GL_LIGHT1, {0.0,0.0,1,1}, {0,0,1,1}, {0,0,1,1});
   luzDir = new LuzDireccional({angulo_alfa,angulo_beta}, GL_LIGHT2, colorAmbiente, colorDifuso, colorEspecular);
}

void Escena::init_materiales()
{
   matBlanco = new Material({0.2,0.2,0.2,1}, {0.9,0.9,0.9,1}, {0,0,0,0}, 10);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   /**************************************************************************/
   // EVALUACIÓN DE VARIABLES
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glShadeModel(GL_SMOOTH);                              // Sombreado suave
   glEnable(GL_NORMALIZE);                               // Normalizar normales

   // Ocultar elementos no visiles
   if (obj == CUADRO) glDisable(GL_CULL_FACE);  // El cuadro al ser una superficie plana, si
   else glEnable(GL_CULL_FACE);                 // no se desactiva solo se vería una cara frontal

   /**************************************************************************/
   // ESCENA

   change_observer();
   draw_axis();
   draw_lights();
   draw_objects();
}

// Dibujado de Objetos

void Escena::draw_objects()
{
   // Si algún modo esta activo, dibujar el objeto correspondiente
   if (puntos or alambre or solido){
      if (obj == CUADRO){
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         cuadro->setMaterial(matBlanco);
         cuadro->draw(puntos, false, false);
         cuadro->draw(false, alambre, false);
         cuadro->draw(false, false, solido);
         glPopMatrix();
      }

      else if (obj == ESFERA){
         esfera->setMaterial(matBlanco);
         esfera->draw(puntos, false, false);
         esfera->draw(false, alambre, false);
         esfera->draw(false, false, solido);
      }

      else if (obj == JERARQUICO){
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
            glScalef(1, 0.5, 0.5);
            modelo->draw(puntos, alambre, solido);
         glPopMatrix();
      }
   }
}

// Dibujado de luces
void Escena::draw_lights()
{
   if (iluminado){
      glEnable(GL_LIGHTING);

      cubo->setMaterial(matBlanco);
      esfera->setMaterial(matBlanco);

      if (luz1) luzPos->activar();
      else luzPos->desactivar();

      if (luz2){
         luzDir->setAnguloAlfa(angulo_alfa);
         luzDir->setAnguloBeta(angulo_beta);
         luzDir->activar();
      }
      else luzDir->desactivar();
   }
   else glDisable(GL_LIGHTING);
}

// Dibujado de Ejes
void Escena::draw_axis()
{
   // Desactivar las luces al dibujar los ejes para que se vean de color
   if (glIsEnabled(GL_LIGHTING)){
      glDisable(GL_LIGHTING);
      ejes.draw();
      glEnable(GL_LIGHTING);
   }
   else ejes.draw();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   bool salir = false;

   switch( toupper(tecla) )
   {
      default:
         cout << "Letra incorrecta" << endl;
         break;

      // SALIR //
      case 'Q':
         if (modoMenu != NADA){
            cout << "\nSELECCIÓN DE MENÚ (OPCIONES: V, M, A, O, Q)" << endl;
            modoMenu = NADA;
         }         
         else{
            if (manual){
               manual = false;
               cout << "MODO MANUAL DESACTIVADO" << endl;
            }
            else salir=true;
         }

         break ;

      // MANUAL //
      case 'M':
         if (modoMenu != VISUALIZACION){
            if (obj == JERARQUICO){
               if (!manual){
                  manual = true;
                  
                  if (animacion){
                     animacion = false;
                     cout << "ANIMACIÓN DESACTIVADA" << endl;
                  }

                  cout << "MODO MANUAL ACTIVADO (OPCIONES: 1, 2, 3, Q)" << endl;
               }
               else cout << "MODO MANUAL YA ACTIVADO" << endl;
            }
            else cout << "Letra incorrecta" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////

      // SELECCIÓN DE MODO DE VISUALIZACION //
      case 'V':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE VISUALIZACIÓN (OPCIONES D, L, S, I, Q)" << endl;
            modoMenu = VISUALIZACION;
         }
         else cout << "Letra incorrecta" << endl;
         break ;
      
      // PUNTOS //
      case 'D':
         if (modoMenu == VISUALIZACION){
            puntos = !puntos;
            iluminado = false;
            
            if (puntos)
               cout << "VISUALIZACIÓN: DOTS ACTIVADO" << endl;
            else
               cout << "VISUALIZACIÓN: DOTS DESACTIVADO" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // ALAMBRE //
      case 'L':
         if (modoMenu == VISUALIZACION){
            alambre = !alambre;
            iluminado = false;

            if (alambre)
               cout << "VISUALIZACIÓN: LÍNEAS ACTIVADO" << endl;
            else
               cout << "VISUALIZACIÓN: LÍNEAS DESACTIVADO" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // SÓLIDO //
      case 'S':
         if (modoMenu == VISUALIZACION){ 
            solido = !solido;
            iluminado = false;

            if (solido)
               cout << "VISUALIZACIÓN: SÓLIDO ACTIVADO" << endl;
            else
               cout << "VISUALIZACIÓN: SÓLIDO DESACTIVADO" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // ILUMINACIÓN //
      case 'I':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               iluminado = false;
               cout << "\nVISUALIZACIÓN: ILUMINACIÓN DESACTIVADA" << endl;
            }
            else{
               iluminado = true;
               cout << "\nVISUALIZACIÓN: ILUMINACIÓN ACTIVADA" << endl
                    << "OPCIONES: 1, 2, A, B, < , >" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////

      // ALFA y ANIMAR //
      case 'A':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               alfa = true;
               beta = false;

               cout << "ALFA ACTIVADO - BETA DESACTIVADO" << endl;
            }
         }

         else{
            animacion = !animacion;

            if (manual){
               manual = false;
               cout << "MODO MANUAL DESACTIVADO" << endl;
            }

            //modelo->animar(velAnimacion);
                        
            if (animacion)
               cout << "ANIMACIÓN ACTIVADA" << endl;
            else
               cout << "ANIMACIÓN DESACTIVADA" << endl;
         }
         break;
         
      // BETA //
      case 'B':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               beta = true;
               alfa = false;

               cout << "BETA ACTIVADO - ALFA DESACTIVADO" << endl;
            }
            else cout << "Letra incorrecta" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // INCREMENTAR //
      case '>':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               if (alfa){
                  angulo_alfa += 0.2;
                  cout << "ALFA: " << angulo_alfa << endl;
               }

               else if (beta){
                  angulo_beta += 0.2;
                  cout << "BETA: " << angulo_beta << endl;
               }
            }
            else cout << "Letra incorrecta" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // DECREMENTAR //
      case '<':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               if (alfa){
                  angulo_alfa -= 0.2;
                  cout << "ALFA: " << angulo_alfa << endl;
               }

               else if (beta){
                  angulo_beta -= 0.2;
                  cout << "BETA: " << angulo_beta << endl;
               }
            }
            else cout << "Letra incorrecta" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////

      // LUZ 1 o 1º Grado Libertad//
      case '1':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               if (luz1){
                  luz1 = false;
                  cout << "LUZ 1 DESACTIVADA" << endl;
               }
               else{
                  luz1 = true;
                  cout << "LUZ 1 ACTIVADA" << endl;
               }
            }
            else cout << "Letra incorrecta" << endl;
         }

         else{
            if (manual){
               if (move == BARRA){
                  move = NONE;
                  cout << "1er Grado de Libertad, BARRA DESACTIVADA" << endl;
               }
               else{
                  move = BARRA;
                  cout << "1er Grado de Libertad, BARRA ACTIVADA" << endl;
               }
            }
         }
         break;

      // LUZ 2 o 2º Grado Libertad//
      case '2':
         if (modoMenu == VISUALIZACION){
            if (iluminado){
               if (luz2){
                  luz2 = false;
                  cout << "LUZ 2 DESACTIVADA" << endl;
               }
               else{
                  luz2 = true;
                  cout << "LUZ 2 ACTIVADA" << endl;
               }
            }
            else cout << "Letra incorrecta" << endl;
         }

         else{
            if (manual){
               if (move == ASIENTO){
                  move = NONE;
                  cout << "2º Grado de Libertad, ASIENTO DESACTIVADO" << endl;
               }
               else{
                  move = ASIENTO;
                  cout << "2º Grado de Libertad, ASIENTO ACTIVADO" << endl;
               }
            }
         }
         break;

      // 3er Grado Libertad //
      case '3':
         if (modoMenu != VISUALIZACION){
            if (manual){
               if (move == ATRACCION){
                  move = NONE;
                  cout << "3er Grado de Libertad, ATRACCION DESACTIVADA" << endl;
               }
               else{
                  move = ATRACCION;
                  cout << "3er Grado de Libertad, ATRACCION ACTIVADA" << endl;
               }
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////

      // AUMENTAR //
      case '+':
         if (modoMenu != VISUALIZACION){
            if (animacion){
               if (velAnimacion <= 2.0) velAnimacion += 0.1;
               cout << "VELOCIDAD DE ANIMACIÓN: " << velAnimacion << endl;
               modelo->animar(velAnimacion);
            }

            if (manual){
               if (move == BARRA){
                  if (velBarra <= 0.0) velBarra += 0.1;
                  cout << "TRASLACIÓN DE LA BARRA: " << velBarra << endl;
               }
               else if (move == ASIENTO){
                  velAsiento = ((int)(velAsiento + 1) % 360);
                  cout << "ROTACIÓN DE LA ASIENTO: " << velAsiento << endl;
               }
               else if (move == ATRACCION){
                  velAtraccion = ((int)(velAtraccion + 1) % 360);
                  cout << "ROTACIÓN DE LA ATRACCIÓN: " << velAtraccion << endl;
               }
               else
                  cout << "Ningún grado de libertad elegido" << endl;

               modelo->setVelocidad(velBarra, velAsiento, velAtraccion);
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;

      // DISMINUIR //
      case '-':
         if (modoMenu != VISUALIZACION){
            if (animacion){
               if (velAnimacion >= 0.2) velAnimacion -= 0.1;
               cout << "VELOCIDAD DE ANIMACIÓN: " << velAnimacion << endl;
               modelo->animar(velAnimacion);
            }

            if (manual){
               if (move == BARRA){
                  if (velBarra > -20) velBarra -= 0.1;
                  cout << "TRASLACIÓN DE LA BARRA: " << velBarra << endl;
               }
               else if (move == ASIENTO){
                  velAsiento = ((int)(velAsiento - 1) % 360);
                  cout << "ROTACIÓN DE LA ASIENTO: " << velAsiento << endl;
               }
               else if (move == ATRACCION){
                  velAtraccion = ((int)(velAtraccion - 1) % 360);
                  cout << "ROTACIÓN DE LA ATRACCIÓN: " << velAtraccion << endl;
               }
               else
                  cout << "Ningún grado de libertad elegido" << endl;

               modelo->setVelocidad(velBarra, velAsiento, velAtraccion);
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////

      // OBJETO //
      case 'O':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE OBJETO (OPCIONES: C, E, J, Q)" << endl;
            modoMenu = OBJETO;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // CUBO //
      case 'C':
         if (modoMenu == OBJETO){
            if (obj == CUADRO){
               obj = NINGUNO;
               cout << "OBJETO: CUADRO DESACTIVADO" << endl;
            }
            else{
               obj = CUADRO;
               cout << "OBJETO: CUADRO ACTIVADO" << endl;
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;

      // ESFERA //
      case 'E':
         if (modoMenu == OBJETO){
            if (obj == ESFERA){
               obj = NINGUNO;
               cout << "OBJETO: ESFERA DESACTIVADA" << endl;
            }
            else{
               obj = ESFERA;
               cout << "OBJETO: ESFERA ACTIVADA" << endl;
            }
         }
         
         else cout << "Letra incorrecta" << endl;
         break;

      // JERARQUICO //
      case 'J':
         if (modoMenu == OBJETO){
            if (obj == JERARQUICO){
               obj = NINGUNO;
               cout << "OBJETO: MODELO JERARQUICO DESACTIVADO" << endl;
            }
            else{
               obj = JERARQUICO;
               cout << "OBJETO: MODELO JERARQUICO ACTIVADO" << endl;
            }
         }
         
         else cout << "Letra incorrecta" << endl;
         break;
   }
   
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
