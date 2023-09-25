/*O (0,0,0)
A (2,0,0)
B (1,2,0)
C (-1,2,0)
D (-2,0,0)
E (-1,-2,0)
F (1,-2,0)*/

#include <math.h>
#include <stdio.h>

// Ejercicio II
void Hexagono (float radio){
	float angulo = (2.0 * M_PI) / 6.0;

	for (int i = 0; i < 6; i++){
		float x = cos(angulo * i) * radio;
		float y = sin(angulo * i) * radio;
		printf("Vérice %i: %f, %f, 0\n", i, x, y);
	}
}

// Ejercicio III
void Angulo (float xA, float yA, float xB, float yB, float xC, float yC){
	float vecABx = xB - xA;
	float vecABy = yB - yA;
	float vecBCx = xC - xB;
	float vecBCy = yC - yB;

	float prodEsc = (vecABx * vecBCx) + (vecABy * vecBCy);
	
	float magAB = sqrt((vecABx * vecABx) + (vecABy * vecABy));
	float magBC = sqrt((vecBCx * vecBCx) + (vecBCy * vecBCy));

	float angulo = acos(prodEsc / (magAB * magBC));
	float anguloGrados = angulo * 180.0 / M_PI;

	printf("\nÁngulo: %f grados\n", anguloGrados);
}

// Ejercicio IV
void Distancia (float xC, float yC, float xD, float yD){
	float dist = sqrt((xD - xC) * (xD - xC) + (yD - yC) * (yD - yC));

	printf("\nDistancia segmento DC: %f\n", dist);
}

// Ejercicio V
// Si el origen de coordenadas estuviera en el punto C en lugar de en el punto 0,
// tendríamos que desplazar los puntos 2 unidades hacia la izquierda en el eje X
// y 1.732 (radio * sen(angulo)) unidades hacia arriba en el eje Y.

// Ejercicio VI
void prodVec(float x1, float y1, float x2, float y2, float x3, float y3){
	float vec1x = x2 - x1;
	float vec1y = y2 - y1;

	float vec2x = x3 -x1;
	float vec2y = y3 -y1;

	float prodVx = vec1y * 0 - 0 * vec2y;
	float prodVy = 0 * vec2x - vec1x * 0;
	float prodVz = vec1x * vec2y - vec1y * vec2x;

	printf("Producto Vectorial: (%f, %f, %f)\n", prodVx, prodVy, prodVz);
}

int main(){
	Hexagono(2.0);
	Angulo(2, 0, 1, 1.732, -1, 1.732);
	Distancia(-1, 1.732, -2, 0);
	
	prodVec(2, 0, 1, 1.732, 1, -1.732);
	prodVec(2, 0, 1, -1.732, 1, 1.732);
	
	return 0;
}

