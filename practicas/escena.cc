

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

   init_camaras();
   camaras[activa]->setProyeccion(UI_window_width, UI_window_height);
   //change_projection( float(UI_window_width)/float(UI_window_height) );
	//glViewport( 0, 0, UI_window_width, UI_window_height );
}

void Escena::init_camaras(){
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   camaras[0] = new Camara({0,50,150}, {0,0,0}, {0,1,0}, 0,
   -Width, Width, -Height, Height, 50.0, 2000.0);

   camaras[1] = new Camara({0,50,-200}, {0,0,0}, {0,1,0}, 0,
   -Width, Width, -Height, Height, Front_plane, Back_plane);

   camaras[2] = new Camara({0,50,150}, {0,0,0}, {0,1,0}, 1,
   -Width, Width, -Height, Height, Front_plane, Back_plane);
}

void Escena::init_objetos()
{
   esfera0 = new Esfera(20, 20, 50);
   esfera1 = new Esfera(20, 20, 50);
   esfera2 = new Esfera(20, 20, 50);

   esfera0->setTextura("../texturas/text-madera.jpg");
   esfera1->setTextura("../texturas/text-mundo.jpg");
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
   glShadeModel(GL_SMOOTH);   // Sombreado suave
   glEnable(GL_NORMALIZE);    // Normalizar normales
   glEnable(GL_CULL_FACE);    // Ocultar elementos no visiles
   

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
   if (puntos or alambre or solido){
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslatef(0,100,0);
         glLoadName(1);
         glPushName(1);
         esfera0->draw(puntos, false, false);
         esfera0->draw(false, alambre, false);
         esfera0->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(100,0,0);
         glLoadName(2);
         glPushName(2);
         esfera1->draw(puntos, false, false);
         esfera1->draw(false, alambre, false);
         esfera1->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-100,0,0);
         glLoadName(3);
         glPushName(3);
         esfera2->draw(puntos, false, false);
         esfera2->draw(false, alambre, false);
         esfera2->draw(false, false, solido);
         glPopName();
      glPopMatrix();
   }
}

// Dibujado de luces
void Escena::draw_lights()
{
   if (iluminado){
      glEnable(GL_LIGHTING);

      esfera0->setMaterial(matBlanco);
      esfera1->setMaterial(matBlanco);
      esfera2->setMaterial(matBlanco);

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

void Escena::dibujarSeleccion(int selected){

   switch (selected){
      case 0:
         esfera0->setSeleccionado(false);
         esfera1->setSeleccionado(false);
         esfera2->setSeleccionado(false);

         camaras[activa]->setAt({0,0,0});
         camaras[activa]->setEstadoRaton(PRIMERA_PERSONA);
         break;

      case 1:
         esfera0->setSeleccionado(true);
         esfera1->setSeleccionado(false);
         esfera2->setSeleccionado(false);

         camaras[activa]->setObjetivo({0,100,100}, {0,100,0});
         break;
      
      case 2:
         esfera0->setSeleccionado(false);
         esfera1->setSeleccionado(true);
         esfera2->setSeleccionado(false);

         camaras[activa]->setObjetivo({50,0,100}, {100,0,0});
         break;

      case 3:
         esfera0->setSeleccionado(false);
         esfera1->setSeleccionado(false);
         esfera2->setSeleccionado(true);

         camaras[activa]->setObjetivo({-100,0,100}, {-100,0,0});
         break;
   }
}

void Escena::pick(int x, int y){
   GLuint buffer[1024];
   GLint hits, viewport[4];

   glGetIntegerv(GL_VIEWPORT, viewport);
   glSelectBuffer(1024, buffer);
   glRenderMode(GL_SELECT);

   glInitNames();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPickMatrix(x,viewport[3]-y,5.0,5.0,viewport);
   glFrustum(-Width, Width, -Height, Height, Front_plane, Back_plane);
   dibujar();

   hits = glRenderMode(GL_RENDER);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-Width, Width, -Height, Height, Front_plane, Back_plane);
   
   if (hits != 0)
      procesarHits(hits, buffer);

   else{
      seleccionado = 0;
      dibujarSeleccion(seleccionado);
      camaras[activa]->setEstadoRaton(PRIMERA_PERSONA);
   }
}

void Escena::procesarHits(GLint hits, GLuint buffer[]){
   GLuint names, minZ, numberOfNames;
   GLuint *ptr, *ptrNames;

   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;

   for (unsigned int i = 0; i < hits; i++){
      names = *ptr;
      ptr++;

      if (*ptr < minZ){
         numberOfNames = names;
         minZ = *ptr;
         ptrNames = ptr+2;
      }

      ptr += names+2;
   }

   seleccionado = *ptrNames;
   dibujarSeleccion(seleccionado);
   camaras[activa]->setEstadoRaton(EXAMINAR);
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

   if (tecla != 88 and tecla != 90 and tecla != 120 and tecla != 122) // X, Z, x, z
      cout << "Tecla pulsada: '" << tecla << "'" << endl;             // en ascii

   bool salir = false;

   switch( toupper(tecla) )
   {
      default:
         cout << "Letra incorrecta" << endl;
         break;

      case 'Z': // Eje Z++
         camaras[activa]->mover(0,0,++Observer_distance);
         break;
      case 'X': // Eje Z--
         camaras[activa]->mover(0,0,--Observer_distance);
         break;

      case 'R': // Reset Camara
         camaras[activa]->setObjetivo({0,50,150}, {0,0,0});
         break;

      // SALIR //
      case 'Q':
         if (seleccionado != 0){
            cout << "\nOBJETO DESELECCIONADO" << endl; 
            seleccionado = 0;
            dibujarSeleccion(seleccionado);
            camaras[activa]->setObjetivo({0,50,150}, {0,0,0});
         }

         else if (modoMenu != NADA){
            cout << "\nSELECCIÓN DE MENÚ (OPCIONES: V, A, C, Q)" << endl;
            modoMenu = NADA;
         }         
         else{
            if (animacion){
               animacion = false;
               cout << "ANIMACIÓN DESACTIVADA" << endl;
            }
            else salir=true;
         }

         break ;

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

      case '0':
         if (modoMenu == CAMARA){
            activa = 0;
            cout << "CÁMARA 0 ACTIVADA" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      // LUZ 1 o CAMARA 1//
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

         else if (modoMenu == CAMARA){
            activa = 1;
            cout << "CÁMARA 1 ACTIVADA" << endl;
         }
         break;

      // LUZ 2 o CAMARA 2//
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

         else if (modoMenu == CAMARA){
            activa = 2;
            cout << "CÁMARA 2 ACTIVADA" << endl;
         }
         break;

      /////////////////

      // SELECCION DE CAMARAS //
      case 'C':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE CÁMARA (OPCIONES: 0, 1, 2, Q)" << endl;
            modoMenu = CAMARA;
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
         camaras[activa]->mover(--Observer_angle_y,0,0);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[activa]->mover(++Observer_angle_y,0,0);
         break;
	   case GLUT_KEY_UP:
         camaras[activa]->mover(0,--Observer_angle_x,0);
         break;
	   case GLUT_KEY_DOWN:
         camaras[activa]->mover(0,++Observer_angle_x,0);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[activa]->zoom(1.2, Width*10, Height*10); //Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[activa]->zoom(-1.2, Width*10, Height*10); //Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
void Escena::clickRaton( int boton, int estado, int x, int y )
{
   if ( boton == GLUT_RIGHT_BUTTON ){
      if ( estado == GLUT_DOWN ){
         if (seleccionado != 0){
            camaras[activa]->setEstadoRaton(EXAMINAR);
            cout << "EXAMINAR" << endl;
         }
         else{ 
            camaras[activa]->setEstadoRaton(PRIMERA_PERSONA);
            cout << "PRIMERA PERSONA" << endl;
         }

         clickDer = true;
         xant = x;
         yant = y;
      }
   }
   else if (boton == GLUT_LEFT_BUTTON){
      clickDer = false;
      camaras[activa]->setEstadoRaton(PRIMERA_PERSONA);
      pick(x,y);
   }
}

//**************************************************************************

void Escena::ratonMovido( int x, int y )
{
   if (clickDer){
      camaras[activa]->mover(x-xant, y-yant, 0); // el movimiento depende del estado del raton

      xant = x;
      yant = y;
   }
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
   camaras[activa]->setProyeccion(newHeight, newWidth);
   //change_projection( float(newHeight)/float(newWidth) );
   //glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[activa]->setObserver();
}
