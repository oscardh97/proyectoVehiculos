#pragma once
#include "mapa.h"
class Vehiculo{
	// int posX, posY, color;
	// string nombre, mensajeExplotar;
	char id, capa,capaEspecial;
protected:
	int estado, resistencia, velocidad;
	Mapa* mapa;
public:
	Vehiculo(int, int, char, int, int);
	// ~Vehiculo();
	// Vehiculo();
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	virtual void avanzar(vector<int*>, Mapa*) = 0;
	void chocar(Vehiculo*);
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	void explotar();
	bool estaVivo();
	virtual bool puedeSeguir(const int,const int, Mapa*) = 0;
	char obtenerId();
	// virtual void toString(char**) const = 0;
};