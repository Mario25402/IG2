

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
   cubo = new Cubo(50);
   piramide = new PiramidePentagonal(50,50);
   cilindro = new Cilindro(4, 20, 100, 50);
   esfera = new Esfera(20, 20, 50);
   cono = new Cono(3, 20, 100, 50);

   ply1 = new ObjRevolucion("../plys_ejemplo/copa.ply", 20);
   ply2 = new ObjPLY("../plys_ejemplo/big_dodge.ply");
   ply3 = new ObjPLY("../plys_ejemplo/beethoven.ply");

   modelo = new ModeloJerarquico();
}

void Escena::init_luces()
{
   angulo_alfa = 0;
   angulo_beta = 0;

   luzPos = new LuzPosicional({0,50,0}, GL_LIGHT1, {0.0,0.0,1,1}, {0,0,1,1}, {0,0,1,1});
   luzDir = new LuzDireccional({angulo_alfa,angulo_beta}, GL_LIGHT2, {0.2,0.2,0.2,1}, {0.4,0.4,0.4,1}, {0.4,0.4,0.4,1});
}

void Escena::init_materiales()
{
   bronce = new Material({0.2125,0.1275,0.054,1}, {0.714,0.4284,0.18144,1}, {0.393548,0.271906,0.166721,1}, 25.6);
   oro = new Material({0.329412,0.223529,0.027451,1}, {0.780392,0.568627,0.113725,1}, {0.992157,0.941176,0.807843,1}, 27.8974);
   perla = new Material({0.25,0.20725,0.20725,0.922}, {1,0.829,0.829,0.922}, {0.296648,0.296648,0.296648,0.922}, 11.264);

   matBlanco = new Material({0.2,0.2,0.2,1}, {0.9,0.9,0.9,1}, {0,0,0,0}, 10);
   matNegro = new Material({0.2,0.2,0.2,1}, {0.2,0.2,0.2,1}, {0.9,0.9,0.9,0.9}, 90);
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
   glEnable(GL_CULL_FACE);                               // Ocultar elementos no visiles
   glShadeModel(GL_SMOOTH);                              // Sombreado suave
   glEnable(GL_NORMALIZE);                               // Normalizar normales

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
      if (obj == CUBO){
         cubo->setMaterial(matBlanco);
         cubo->draw(puntos, false, false);
         cubo->draw(false, alambre, false);
         cubo->draw(false, false, solido);
      }
         
      else if (obj == PIRAMIDE){
         piramide->setMaterial(matBlanco);
         piramide->draw(puntos, false, false);
         piramide->draw(false, alambre, false);
         piramide->draw(false, false, solido);
      }

      else if (obj == PLY){
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         if (objPlySel == PLY1){
            glTranslatef(0, -15 * ply1->centrar(), 0);
            glScalef(15, 15, 15);

            ply1->setMaterial(matBlanco);
            ply1->draw(puntos, false, false);
            ply1->draw(false, alambre, false);
            ply1->draw(false, false, solido);
         }

         else if (objPlySel == PLY2){
            glTranslatef(0, -10 * ply2->centrar(), 0);
            glScalef(10, 10, 10);

            ply1->setMaterial(matBlanco);
            ply2->draw(puntos, false, false);
            ply2->draw(false, alambre, false);
            ply2->draw(false, false, solido);
         }

         else if (objPlySel == PLY3){
            glTranslatef(0, -10 * ply3->centrar(), 0);
            glScalef(10, 10, 10);

            ply3->setMaterial(matBlanco);
            ply3->draw(puntos, false, false);
            ply3->draw(false, alambre, false);
            ply3->draw(false, false, solido);
         }
      }

      else if (obj == CILINDRO){
         cilindro->setMaterial(bronce);
         cilindro->draw(puntos, false, false);
         cilindro->draw(false, alambre, false);
         cilindro->draw(false, false, solido);
      }

      else if (obj == ESFERA){
         esfera->setMaterial(matBlanco);
         esfera->draw(puntos, false, false);
         esfera->draw(false, alambre, false);
         esfera->draw(false, false, solido);
      }

      else if (obj == CONO){
         cono->setMaterial(matBlanco);
         cono->draw(puntos, false, false);
         cono->draw(false, alambre, false);
         cono->draw(false, false, solido);
      }

      else if (obj == MULTIPLE){
         // Cilindro
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         glTranslatef(0, 0, -75);
         cilindro->setMaterial(bronce);
         cilindro->draw(puntos, false, false);
         cilindro->draw(false, alambre, false);
         cilindro->draw(false, false, solido);

         glPopMatrix();

         // Cono
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         glTranslatef(-75, 0, 75);
         cono->setMaterial(oro);
         cono->draw(puntos, false, false);
         cono->draw(false, alambre, false);
         cono->draw(false, false, solido);

         glPopMatrix();

         // Esfera
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         glTranslatef(75, esfera->getRadio() , 75); 
         esfera->setMaterial(perla);
         esfera->draw(puntos, false, false);
         esfera->draw(false, alambre, false);
         esfera->draw(false, false, solido);

         glPopMatrix();
      }

      else if (obj == VECTOR){
         glMatrixMode(GL_MODELVIEW);
         glPushMatrix();

         glTranslatef(-75, -50 * rev->centrar(), 0);
         glScalef(50, 50, 50);
         rev->setMaterial(matBlanco);
         rev->draw(puntos, false, false);
         rev->draw(false, alambre, false);
         rev->draw(false, false, solido);

         glPopMatrix();
         glPushMatrix();

         glTranslatef(75, -50 * rev->centrar(), 0);
         glScalef(50, 50, 50);
         rev->setMaterial(matNegro);
         rev->draw(puntos, false, false);
         rev->draw(false, alambre, false);
         rev->draw(false, false, solido);

         glPopMatrix();
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

void Escena::animarModeloJerarquico()
{
   modelo->animar();
}

// Dibujado de luces
void Escena::draw_lights()
{
   if (iluminado){
      glEnable(GL_LIGHTING);

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
            cout << "\nSELECCIÓN DE MENÚ (OPCIONES: O, V, Q)" << endl;
            modoMenu = NADA;
         }
         
         else salir=true;
         break ;

      /////////////////
      // MODO SELECCIÓN DE OBJETO

      case 'O':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE OBJETO (OPCIONES C, P, Y, E, R, N, M, 4, J, Q)" << endl;
            modoMenu = SELOBJETO; 
         }
         else cout << "Letra incorrecta" << endl;
         break ;

      // CUBO //
      case 'C':
         if (modoMenu == SELOBJETO){
            if (obj == CUBO){
               obj = NINGUNO;
               cout << "OBJETO: CUBO DESACTIVADO" << endl;
            }
            else{
               obj = CUBO;
               cout << "OBJETO: CUBO ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // PIRÁMIDE //
      case 'P':
         if (modoMenu == SELOBJETO){
            if (obj == PIRAMIDE){
               obj = NINGUNO;
               cout << "OBJETO: PIRÁMIDE DESACTIVADO" << endl;
            }
            else{
               obj = PIRAMIDE;
               cout << "OBJETO: PIRÁMIDE ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // PLY //
      case 'Y':
         if (modoMenu == SELOBJETO){
            if (obj == PLY){
               obj = NINGUNO;
               cout << "OBJETO: PLY DESACTIVADO" << endl;
            }
            else{
               obj = PLY;
               cout << "OBJETO: PLY ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // CILINDRO //
      case 'R':
         if (modoMenu == SELOBJETO){
            if (obj == CILINDRO){
               obj = NINGUNO;
               cout << "OBJETO: CILINDRO DESACTIVADO" << endl;
            }
            else{
               obj = CILINDRO;
               cout << "OBJETO: CILINDRO ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // ESFERA //
      case 'E':
         if (modoMenu == SELOBJETO){
            if (obj == ESFERA){
               obj = NINGUNO;
               cout << "OBJETO: ESFERA DESACTIVADO" << endl;
            }
            else{
               obj = ESFERA;
               cout << "OBJETO: ESFERA ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // CONO //
      case 'N':
         if (modoMenu == SELOBJETO){
            if (obj == CONO){
               obj = NINGUNO;
               cout << "OBJETO: CONO DESACTIVADO" << endl;
            }
            else{
               obj = CONO;
               cout << "OBJETO: CONO ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // MÚLTIPLE //
      case 'M':
         if (modoMenu == SELOBJETO){
            if (obj == MULTIPLE){
               obj = NINGUNO;
               cout << "OBJETO: MÚLTIPLE DESACTIVADO" << endl;
            }
            else{
               obj = MULTIPLE;
               cout << "OBJETO: MÚLTIPLE ACTIVADO" << endl;
            }
         }
         break ;

      // MODELO JERARQUICO //
      case 'J':
         if (modoMenu == SELOBJETO){
            if (obj == JERARQUICO){
               obj = NINGUNO;
               cout << "OBJETO: MODELO JERARQUICO DESACTIVADO" << endl;
            }
            else{
               obj = JERARQUICO;
               cout << "OBJETO: MODELO JERARQUICO ACTIVADO" << endl;
            }
         }
         break ;

      /////////////////
      // SELECCIÓN DE MODO DE VISUALIZACION //

      case 'V':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE VISUALIZACIÓN (OPCIONES D, L, S, I, Q)" << endl;
            modoMenu = SELVISUALIZACION;
         }
         else cout << "Letra incorrecta" << endl;
         break ;
      
      // PUNTOS //
      case 'D':
         if (modoMenu == SELVISUALIZACION){
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
         if (modoMenu == SELVISUALIZACION){
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
         if (modoMenu == SELVISUALIZACION){ 
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
         if (modoMenu == SELVISUALIZACION){
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
      // MODIFICACIÓN DE VARIABLES DE ILUMINACIÓN //
      // SELECCIÓN DE OBJETO PLYS //

      // LUZ 1 o PLY 1//
      case '1':
         if (modoMenu == SELOBJETO){
            if (obj == PLY){
               if (objPlySel == PLY1){
                  objPlySel = NONE;
                  cout << "OBJETO: PLY1 DESACTIVADO" << endl;
               }
               else{
                  objPlySel = PLY1;
                  cout << "OBJETO: PLY1 ACTIVADO" << endl;
               }
            }
            else cout << "Letra incorrecta" << endl;
         }

         else if (modoMenu == SELVISUALIZACION){
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

         else cout << "Letra incorrecta" << endl;
         break;

      // LUZ 2 o PLY 2 //
      case '2':
         if (modoMenu == SELOBJETO){
            if (obj == PLY){
               if (objPlySel == PLY2){
                  objPlySel = NONE;
                  cout << "OBJETO: PLY2 DESACTIVADO" << endl;
               }
               else{
                  objPlySel = PLY2;
                  cout << "OBJETO: PLY2 ACTIVADO" << endl;
               }
            }
         }

         else if (modoMenu == SELVISUALIZACION){
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

         else cout << "Letra incorrecta" << endl;
         break;

      // PLY 3 //
      case '3':
         if (modoMenu == SELOBJETO){
            if (obj == PLY){
               if (objPlySel == PLY3){
                  objPlySel = NONE;
                  cout << "OBJETO: PLY3 DESACTIVADO" << endl;
               }
               else{
                  objPlySel = PLY3;
                  cout << "OBJETO: PLY3 ACTIVADO" << endl;
               }
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // VECTOR DE PUNTOS//
      case '4':
         if (modoMenu == SELOBJETO){
            if (obj == VECTOR){
               obj = NINGUNO;
               delete rev;
               cout << "OBJETO: VECTOR DE PUNTOS DESACTIVADO" << endl;
            }
            else{
               obj = VECTOR;
               cout << "OBJETO: VECTOR DE PUNTOS ACTIVADO" << endl;

               std::vector<Tupla3f> perfil;
               perfil.push_back(Tupla3f(0.0, -1.4, 0.0));
               perfil.push_back(Tupla3f(1, -1.4, 0.0));
               perfil.push_back(Tupla3f(1, -1.1, 0.0));
               perfil.push_back(Tupla3f(0.5, -0.7, 0.0));
               perfil.push_back(Tupla3f(0.4, -0.4, 0.0));
               perfil.push_back(Tupla3f(0.4, 0.5, 0.0));
               perfil.push_back(Tupla3f(0.5, 0.6, 0.0));
               perfil.push_back(Tupla3f(0.3, 0.6, 0.0));
               perfil.push_back(Tupla3f(0.5, 0.8, 0.0));
               perfil.push_back(Tupla3f(0.55, 1.0, 0.0));
               perfil.push_back(Tupla3f(0.5, 1.2, 0.0));
               perfil.push_back(Tupla3f(0.3, 1.4, 0.0));
               perfil.push_back(Tupla3f(0.0, 1.4, 0.0));

               rev = new ObjRevolucion(perfil, 20);
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // ALFA //
      case 'A':
         if (modoMenu == SELVISUALIZACION){
            if (iluminado){
               alfa = true;
               beta = false;

               cout << "ALFA ACTIVADO - BETA DESACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;
         
      // BETA //
      case 'B':
         if (modoMenu == SELVISUALIZACION){
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
         if (modoMenu == SELVISUALIZACION){
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
         if (modoMenu == SELVISUALIZACION){
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
