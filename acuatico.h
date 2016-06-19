#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
class Acuatico : public Vehiculo{
public:
	Acuatico(int, int, char, int, int);
	// ~vehiculo();/*/
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	void avanzar(vector<int*>, Mapa*);
	bool puedeSeguir(const int,const int, Mapa*);
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	// void explotar();
	// bool estaVivo();
	// char obtenerId();
};