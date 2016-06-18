#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
class Terrestre : public Vehiculo{
public:
	Terrestre(int, int, char);
	// ~vehiculo();/*/
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	virtual void avanzar(vector<int*>, Mapa*);
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	// void explotar();
	// bool estaVivo();
	// char obtenerId();
};