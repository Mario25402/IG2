// Ejercicio 30
struct vertices1{
	float x;
	float y;
	float z;
};

struct malla{
	vertices1[] tri;
	int numTri;
};

// Ejercicio 31

vertices1 prodVec(vertices1 A, vertices1 B){
	vertices1 res;

	res.x = A.x * B.z - A.z * B.y;
	res.y = A.z * B.x - A.x * B.z;
	res.z = A.x * B.y - A.y * B.y;

	return res;
}

float areaMalla(malla m){
	float area = 0;

	for (int i = 0; i < m.numTri; i++){
		vertices1 AB;
		vertices1 AC;

		AB.x = m.tri[i+1].x - m.tri[i].x;
		AB.y = m.tri[i+1].y - m.tri[i].y;
		AB.z = m.tri[i+1].z - m.tri[i].z;

		AC.x = m.tri[i+2].x - m.tri[i].x;
		AC.y = m.tri[i+2].y - m.tri[i].y;
		AC.z = m.tri[i+2].z - m.tri[i].z;

		vertices1 res = prodVec(AB, AC);
		area += 0.5 * sqrt(res.x * res.x + res.y * res.y + res.z * res.z);
	}

	return area;
}


// Ejercicio 32

struct vertices2{
	float x, y, z;
	float arista;
};

struct cara{
	float arista;
};

struct aristaAlada{
	vertices2 v1, v2;
	cara caraIzda, caraDcha;

	aristaAlada aristaSigDcha;
	aristaAlada aristaSigIzda;
	aristaAlada aristaAntDcha;
	aristaAlada aristaAntIzda
};

void rellenaAristaAlada(malla m){
	for (int i = 1; i < m.numTri; i++){
		aristaAlada a;
		a.v1 = m.tri[i];
		a.v2 = m.tri[i+1];
		a.caraIzda = m.tri[i+2];
		a.caraDcha = m.tri[i+3];

		a.aristaSigDcha = m.tri[i+1];
		a.aristaSigIzda = m.tri[i+2];
		a.aristaAntDcha = m.tri[i+3];
		a.aristaAntIzda = m.tri[i];
	}
}

// Ejercicio 34

struct semiaristaAlada
{
	vertices2 v;
	cara c;

	semiaristaAlada sig;
	semiaristaAlada ant;
	semiaristaAlada op;
};

// Ejercicio 35

float numeroMedioCarasPorVertice(semiaristaAlada *s){
	int numV = 0, numC = 0;

	semiaristaAlada *actual = s;

	do{
		numV++;
		if (actual == s) numC++;

		actual = actual->ant;
	} while (actual != s);
	
	return numC / numV;
}

// Ejercicio 37

vertices1 calcNormales(vertices1 v){
	// calcular las normales de un triangulo dados sus 3 vertices

	vertices1 AB;
	vertices1 AC;

	AB.x = v[1].x - v[0].x;
	AB.y = v[1].y - v[0].y;
	AB.z = v[1].z - v[0].z;

	AC.x = v[2].x - v[0].x;
	AC.y = v[2].y - v[0].y;
	AC.z = v[2].z - v[0].z;

	vertices1 res = prodVec(AB, AC);
	float modulo = sqrt(res.x * res.x + res.y * res.y + res.z * res.z);

	res.x /= modulo;
	res.y /= modulo;
	res.z /= modulo;

	return res;
}

// Ejercicio 38

void calcNormalesMalla(semiaristaAlada *s){
	semiaristaAlada *actual = s;

	do{
		vertices1 normales = calcNormales(actual->c);
		actual->v.x = normales.x;
		actual->v.y = normales.y;
		actual->v.z = normales.z;

		actual = actual->sig;
	} while (actual != s);
}

// Ejercicio 39
malla copiaMalla(malla m, float d){
	malla res;

	for (int i = 0; i < m.numTri; i++){
		vertices1 normales = calcNormales(m.tri[i]);
		m.tri[i].x += normales.x * d;
		m.tri[i].y += normales.y * d;
		m.tri[i].z += normales.z * d;
	}

	return res;
}