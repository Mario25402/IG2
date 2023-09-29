

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

    cubo = new Cubo(50);
    piramide = new PiramidePentagonal(50,50);
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



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
   glEnable(GL_CULL_FACE);
	
   change_observer();
   ejes.draw();

   if (obj == CUBO) cubo->draw(puntos, alambre, solido);
   else if (obj == PIRAMIDE) piramide->draw(puntos, alambre, solido);
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
   static objeto anterior = NINGUNO;

   switch( toupper(tecla) )
   {
      default:
         cout << "Letra incorrecta" << endl;
         break;

      case 'Q' :
         if (modoMenu != NADA){
            cout << "\nSELECCIÓN DE MENÚ (OPCIONES: O, V, Q)" << endl;
            modoMenu = NADA;
         }
         
         else salir=true;
         break ;

      /////////////////
      // ESTAMOS EN MODO SELECCION DE OBJETO

      case 'O' :
         cout << "\nSELECCIÓN DE OBJETO (OPCIONES C, P, Q)" << endl;
         modoMenu=SELOBJETO; 
         break ;

      case 'C':
         if (modoMenu == SELOBJETO){
            if (obj == CUBO){
               obj = NINGUNO;
               anterior = obj;
               cout << "OBJETO: CUBO DESACTIVADO" << endl;
            }
            else{
               obj = CUBO;
               anterior = obj;
               cout << "OBJETO: CUBO ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      case 'P':
         if (modoMenu == SELOBJETO){
            if (obj == PIRAMIDE){
               obj = NINGUNO;
               anterior = obj;
               cout << "OBJETO: PIRÁMIDE DESACTIVADO" << endl;
            }
            else{
               obj = PIRAMIDE;
               anterior = obj;
               cout << "OBJETO: PIRÁMIDE ACTIVADO" << endl;
            }
         }
         else cout << "Letra incorrecta" << endl;
         break;

      /////////////////
      // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION

      case 'V':
         cout << "\nSELECCIÓN DE VISUALIZACIÓN (OPCIONES D, L, S, Q)" << endl;
         modoMenu=SELVISUALIZACION;
         break ;
      
      case 'D':
         if (modoMenu == SELVISUALIZACION){
            puntos = !puntos;
            
            if (puntos)
               cout << "VISUALIZACIÓN: DOTS ACTIVADA" << endl;
            else
               cout << "VISUALIZACIÓN: DOTS DESACTIVADA" << endl;

            if (!puntos and !alambre and !solido)
               obj = NINGUNO;
            else
               obj = anterior;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      case 'L':
         if (modoMenu == SELVISUALIZACION){
            alambre = !alambre;

            if (alambre)
               cout << "VISUALIZACIÓN: LÍNEAS ACTIVADA" << endl;
            else
               cout << "VISUALIZACIÓN: LÍNEAS DESACTIVADA" << endl;

            if (!puntos and !alambre and !solido)
               obj = NINGUNO;
            else
               obj = anterior;
         }
         else cout << "Letra incorrecta" << endl;
         break;

      case 'S':
         if (modoMenu == SELVISUALIZACION){ 
            solido = !solido;

            if (solido)
               cout << "VISUALIZACIÓN: SÓLIDO ACTIVADO" << endl;
            else
               cout << "VISUALIZACIÓN: SÓLIDO DESACTIVADO" << endl;

            if (!puntos and !alambre and !solido)
               obj = NINGUNO;
            else
               obj = anterior;
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