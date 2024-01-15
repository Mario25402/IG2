

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

   init_materiales();
   init_luces();
   init_objetos();
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
   if (animacionPosicional){
      luzPos->animarPosicion();
   }
}

void Escena::animarLuzDireccional(){
   if (animacionDireccional){
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

   Observer_angle_x = camaras[0]->getEye()[0];
   Observer_angle_y = camaras[0]->getEye()[1];
   Observer_distance = camaras[0]->getEye()[2];
}

void Escena::init_objetos()
{
   vector<Tupla3f> perfil;
   perfil.push_back({0.0, -1.4, 0.0});
   perfil.push_back({1, -1.4, 0.0});
   perfil.push_back({1, -1.1, 0.0});
   perfil.push_back({0.5, -0.7, 0.0});
   perfil.push_back({0.4, -0.4, 0.0});
   perfil.push_back({0.4, 0.5, 0.0});
   perfil.push_back({0.5, 0.6, 0.0});
   perfil.push_back({0.3, 0.6, 0.0});
   perfil.push_back({0.5, 0.8, 0.0});
   perfil.push_back({0.55, 1.0, 0.0});
   perfil.push_back({0.5, 1.2, 0.0});
   perfil.push_back({0.3, 1.4, 0.0});
   perfil.push_back({0.0, 1.4, 0.0});

   /////

   modelo = new ModeloJerarquico();
   cono = new Cono(3, 20, 100, 50);
   cuadro = new Cuadro(100);

   ply = new ObjPLY("../plys_ejemplo/beethoven.ply");
   copa = new ObjRevolucion("../plys_ejemplo/copa.ply", 25);
   peon = new ObjRevolucion(perfil, 25);

   /////

   modelo->setTextura();
   cuadro->setTextura("../texturas/text-mundo.jpg");
}

void Escena::init_luces()
{
   angulo_alfa = 0;
   angulo_beta = 0;
   
   luzPos = new LuzPosicional({100,0,0}, GL_LIGHT1, {0.0,0.0,1,1}, {0,0,1,1}, {0,0,1,1});
   luzDir = new LuzDireccional({angulo_alfa,angulo_beta}, GL_LIGHT2, {0.2,0.2,0.2,1}, {0.4,0.4,0.4,1}, {0.4,0.4,0.4,1});
}

void Escena::init_materiales()
{
   matCromado = new Material({0.25, 0.25, 0.25, 1}, {0.4, 0.4, 0.4, 1}, {0.774597, 0.774597, 0.774597, 1}, 76.8);
   matCyan =    new Material({0, 0.1, 0.06, 1}, {0,0.50980392, 0.50980392, 1}, {0.50196078, 0.50196078, 0.50196078, 1}, 32);
   matRojo =    new Material({0.05, 0, 0, 1}, {0.5, 0.4, 0.4, 1}, {0.7, 0.04, 0.04, 1}, 10);
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

void Escena::draw_objects()
{
   if (puntos or alambre or solido){
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glScalef(0.1,0.1,0.1);
         glLoadName(1);
         glPushName(1);
         modelo->setMaterial(matCromado);
         modelo->draw(puntos, false, false);
         modelo->draw(false, alambre, false);
         modelo->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-100,0,0);
      glScalef(0.5, 0.5, 0.5);
         glLoadName(2);
         glPushName(2);
         cono->setMaterial(matRojo);
         cono->draw(puntos, false, false);
         cono->draw(false, alambre, false);
         cono->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0,-75,0);
         glLoadName(3);
         glPushName(3);
         cuadro->setMaterial(matCromado);
         cuadro->draw(puntos, false, false);
         cuadro->draw(false, alambre, false);
         cuadro->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(100,30,0);
      glScalef(5,5,5);
         glLoadName(4);
         glPushName(4);
         ply->setMaterial(matRojo);
         ply->draw(puntos, false, false);
         ply->draw(false, alambre, false);
         ply->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-150,0,0);
      glScalef(5,5,5);
         glLoadName(5);
         glPushName(5);
         copa->setMaterial(matCyan);
         copa->draw(puntos, false, false);
         copa->draw(false, alambre, false);
         copa->draw(false, false, solido);
         glPopName();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(150,30,0);
      glScalef(20,20,20);
         glLoadName(6);
         glPushName(6);
         peon->setMaterial(matCyan);
         peon->draw(puntos, false, false);
         peon->draw(false, alambre, false);
         peon->draw(false, false, solido);
         glPopName();
      glPopMatrix();
   }
}

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

/*****************************************************************************/

void Escena::dibujarSeleccion(int selected){
   switch (selected){
      case 0:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(false);
         copa->setSeleccionado(false);
         peon->setSeleccionado(false);

         camaras[activa]->setAt({0,0,0});
         camaras[activa]->setEstadoCamara(PRIMERA_PERSONA);
         break;

      case 1:
         modelo->setSeleccionado(true);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(false);
         copa->setSeleccionado(false);
         peon->setSeleccionado(false);

         camaras[activa]->setObjetivo({0,50,100}, {0,50,0});
         break;
      
      case 2:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(true);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(false);
         copa->setSeleccionado(false);
         peon->setSeleccionado(false);

         camaras[activa]->setObjetivo({-100,50,100}, {-100,0,0});
         break;

      case 3:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(true);
         ply->setSeleccionado(false);
         copa->setSeleccionado(false);
         peon->setSeleccionado(false);

         camaras[activa]->setObjetivo({0,-25,100}, {0,-75,0});
         break;

      case 4:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(true);
         copa->setSeleccionado(false);
         peon->setSeleccionado(false);

         camaras[activa]->setObjetivo({100,50,100}, {100,30,0});
         break;

      case 5:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(false);
         copa->setSeleccionado(true);
         peon->setSeleccionado(false);

         camaras[activa]->setObjetivo({-150,50,100}, {-150,0,0});
         break;

      case 6:
         modelo->setSeleccionado(false);
         cono->setSeleccionado(false);
         cuadro->setSeleccionado(false);
         ply->setSeleccionado(false);
         copa->setSeleccionado(false);
         peon->setSeleccionado(true);

         camaras[activa]->setObjetivo({150,50,100}, {150,30,0});
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
      camaras[activa]->setEstadoCamara(PRIMERA_PERSONA);
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
   camaras[activa]->setEstadoCamara(EXAMINAR);
}

//**************************************************************************

void Escena::clickRaton( int boton, int estado, int x, int y )
{
   if ( boton == GLUT_RIGHT_BUTTON ){ // click derecho
      if ( estado == GLUT_DOWN ){
         if (seleccionado != 0){
            camaras[activa]->setEstadoCamara(EXAMINAR);
         }
         else{ 
            camaras[activa]->setEstadoCamara(PRIMERA_PERSONA);
         }

         clickDer = true;
         xant = x;
         yant = y;
      }
   }

   else if (boton == GLUT_LEFT_BUTTON){ // click izquierdo
      static int i = 0; // Conseguimos que solo actue en el press y no en el realese 

      if (i % 2 == 0){
         clickDer = false;
         camaras[activa]->setEstadoCamara(PRIMERA_PERSONA);
         pick(x,y);
      }

      i++;
   }

   else if (boton == 3) // rueda hacia delante
      camaras[activa]->zoom(-1.2, Width*10, Height*10);
   
   else if(boton == 4) // rueda hacia atrás
      camaras[activa]->zoom(1.2, Width*10, Height*10);
}

void Escena::ratonMovido( int x, int y )
{
   if (clickDer){
      if (camaras[activa]->getEstadoCamara() == EXAMINAR)
         camaras[activa]->mover(x, y, LIMITE, 1);
      else
         camaras[activa]->mover(x-xant, y-yant, LIMITE, 1);

      xant = x;
      yant = y;
   }
}

//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;

   if (tecla != 88 and tecla != 90 and tecla != 120 and tecla != 122) // X, Z, x, z
      cout << "\nTecla pulsada: '" << tecla << "'" << endl;             // en ascii

   bool salir = false;

   switch( toupper(tecla) )
   {
      default:
         cout << "Letra incorrecta" << endl;
         break;

      /////////////////
      // Teclas propias

      case 'Z': // Eje Z++
         camaras[activa]->mover(LIMITE,LIMITE,++Observer_distance, 0);
         break;

      case 'X': // Eje Z--
         camaras[activa]->mover(LIMITE,LIMITE,--Observer_distance, 0);
         break;

      case 'R': // Reset Camara
         camaras[activa]->setObjetivo({0,50,150}, {0,0,0});
         camaras[activa]->setUp({0,1,0});
         break;

      /////////////////
      // Salir

      case 'Q':
         if (seleccionado != 0){
            cout << "\nOBJETO DESELECCIONADO" << endl; 
            seleccionado = 0;
            dibujarSeleccion(seleccionado);
            camaras[activa]->setObjetivo({0,50,150}, {0,0,0});
         }

         else if (modoMenu != NADA){
            cout << "\nSELECCIÓN DE MENÚ" << endl
                 << "   V: Modos de visualización" << endl
                 << "   A: Animación automática del modelo jerárquico" << endl
                 << "   M: Animación manual del modelo jerárquico" << endl
                 << "   C: Selección de cámara" << endl
                 << "   Q: Salir" << endl;

            modoMenu = NADA;
         }   
         else salir = true;
         break ;

      /////////////////
      // Teclas de visualización y animación de la luz posicional

      // SELECCIÓN DE MODO DE VISUALIZACION //
      case 'V':
         if (modoMenu == NADA){
            cout << "\nMODOS DE VISUALIZACIÓN" << endl
                 << "   P: Modo puntos" << endl
                 << "   L: Modo líneas" << endl
                 << "   S: Modo sólido" << endl
                 << "   I: Modo ilumniación" << endl
                 << "   Q: Salir" << endl;

            modoMenu = VISUALIZACION;
         }
         else cout << "Letra incorrecta" << endl;
         break ;
      
      // PUNTOS o ANIMACIÓN LUZ POSICIONAL //
      case 'P':
         if (iluminado){
            animacionPosicional = !animacionPosicional;

            cout << "ANIMACIÓN LUZ POSICIONAL "; 

            if (!animacionPosicional)
               cout << "DES";
            
            cout << "ACTIVADA" << endl;
         }

         else if (modoMenu == VISUALIZACION){
            puntos = !puntos;
            iluminado = false;
            
            if (puntos)
               cout << "VISUALIZACIÓN: PUNTOS ACTIVADO" << endl;
            else
               cout << "VISUALIZACIÓN: PUNTOS DESACTIVADO" << endl;
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
                    << "   I: Desactivar iluminación" << endl
                    << "   1: Luz 1" << endl
                    << "   2: Luz 2" << endl
                    << "   A: Variación de alfa" << endl
                    << "   B: Variación de beta" << endl
                    << "   <: Decrementar" << endl
                    << "   >: Incrementar" << endl
                    << "   D: Animación luz direccional" << endl
                    << "   P: Animación luz posicional" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////
      // Teclas de ilumnación y animación del modelo jerárquico

      // ANIMACIÓN DIRECCIONAL //
      case 'D':
         if (iluminado){
            animacionDireccional = !animacionDireccional;

            cout << "ANIMACIÓN LUZ DIRECCIONAL "; 

            if (!animacionDireccional)
               cout << "DES";
            
            cout << "ACTIVADA" << endl;
         }
         break;

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
                        
            if (animacion){
               cout << "ANIMACIÓN ACTIVADA" << endl
                     << "   +: Incrementar velocidad" << endl
                     << "   -: Decrementar velocidad" << endl;
            }
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
      // Teclas de cámara y selección de luces y grados de libertad

      // SELECCION DE CAMARAS //
      case 'C':
         if (modoMenu == NADA){
            cout << "\nSELECCIÓN DE CÁMARA" << endl
                 << "   0: Cámara 0" << endl
                 << "   1: Cámara 1" << endl
                 << "   2: Cámara 2" << endl
                 << "   Q: Salir" << endl;

            modoMenu = CAMARA;
         }

         else cout << "Letra incorrecta" << endl;
         break;

      // CAMARA 0 o 1er Grado de Libertad //
      case '0':
         if (modoMenu == CAMARA){
            activa = 0;
            seleccionado = 0;
            dibujarSeleccion(seleccionado);

            Observer_angle_x = camaras[0]->getEye()[0];
            Observer_angle_y = camaras[0]->getEye()[1];
            Observer_distance = camaras[0]->getEye()[2];
            
            cout << "CÁMARA 0 ACTIVADA" << endl;
         }

         else if (manual){
            move = BARRA;
            cout << "TRASLACIÓN DE LA BARRA" << endl;
         }

         else cout << "Letra incorrecta" << endl;
         break;

      // LUZ 1 o CAMARA 1 o 2º Grado de Libertad//
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
            seleccionado = 0;
            dibujarSeleccion(seleccionado);

            Observer_angle_x = camaras[1]->getEye()[0];
            Observer_angle_y = camaras[1]->getEye()[1];
            Observer_distance = camaras[1]->getEye()[2];
            
            cout << "CÁMARA 1 ACTIVADA" << endl;
         }

         else if (manual){
            move = ASIENTO;
            cout << "MOVIMIENTO GIRATORIO DEL ASIENTO" << endl;
         }

         else cout << "Letra incorrecta" << endl;
         break;

      // LUZ 2 o CAMARA 2 o 3er Grado de Libertad//
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
            seleccionado = 0;
            dibujarSeleccion(seleccionado);

            Observer_angle_x = camaras[2]->getEye()[0];
            Observer_angle_y = camaras[2]->getEye()[1];
            Observer_distance = camaras[2]->getEye()[2];
            
            cout << "CÁMARA 2 ACTIVADA" << endl;
         }

         else if (manual){
            move = ATRACCION;
            cout << "MOVIMIENTO GIRATORIO DE LA ATRACCION" << endl;
         }

         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////
      // Teclas de movimiento manual

      case 'M':
         if (modoMenu == NADA){
         manual = !manual;

         if (animacion){
            animacion = false;
            cout << "ANIMACIÓN DESACTIVADA" << endl;
         }
                     
         if (manual){
            cout << "MODO MANUAL ACTIVADO" << endl
                 << "   0: Mover barra" << endl
                 << "   1: Mover asiento" << endl
                 << "   2: Mover atracción" << endl
                 << "   +: Incrementar velocidad" << endl
                 << "   -: Decrementar velocidad" << endl;
         }
         else
            cout << "MODO MANUAL DESACTIVADO" << endl;
         }
         else cout << "Letra incorrecta" << endl;
         break;

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
                  velAsiento = fmod(velAsiento++, 360);
                  cout << "ROTACIÓN DE LA ASIENTO: " << velAsiento << endl;
               }
               else if (move == ATRACCION){
                  velAtraccion = fmod(velAtraccion++, 360);
                  cout << "ROTACIÓN DE LA ATRACCIÓN: " << velAtraccion << endl;
               }
               else
                  cout << "Ningún grado de libertad elegido" << endl;

               modelo->setVelocidad(velBarra, velAsiento, velAtraccion);
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;

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
                  velAsiento = fmod(velAsiento--, 360);
                  cout << "ROTACIÓN DE LA ASIENTO: " << velAsiento << endl;
               }
               else if (move == ATRACCION){
                  velAtraccion = fmod(velAtraccion--, 360);
                  cout << "ROTACIÓN DE LA ATRACCIÓN: " << velAtraccion << endl;
               }
               else
                  cout << "Ningún grado de libertad elegido" << endl;

               modelo->setVelocidad(velBarra, velAsiento, velAtraccion);
            }
         }

         else cout << "Letra incorrecta" << endl;
         break;
   }
   
   return salir;
}

/*                *******************************                          */

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[activa]->mover(--Observer_angle_y,LIMITE,LIMITE, 0);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[activa]->mover(++Observer_angle_y,LIMITE,LIMITE, 0);
         break;
	   case GLUT_KEY_UP:
         camaras[activa]->mover(LIMITE,++Observer_angle_x,LIMITE, 0);
         break;
	   case GLUT_KEY_DOWN:
         camaras[activa]->mover(LIMITE,--Observer_angle_x,LIMITE, 0);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[activa]->zoom(1.2, Width*10, Height*10);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[activa]->zoom(-1.2, Width*10, Height*10);
         break;
	}
}

//**************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   camaras[activa]->setProyeccion(newHeight, newWidth);
}

void Escena::change_observer()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[activa]->setObserver();
}

//**************************************************************************