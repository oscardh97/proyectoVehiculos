#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
#include <string>
#include <sstream>
class Terrestre : public Vehiculo{
public:
	Terrestre(int, int, char, int, int, int);
	// ~vehiculo();/*/
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	void avanzar(vector<int*>, Mapa*);
	bool puedeSeguir(const int,const int, Mapa*);
	string toString();
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	// void explotar();
	// bool estaVivo();
	// char obtenerId();
};