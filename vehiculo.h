#pragma once
#include "mapa.h"
class Vehiculo{
	// int posX, posY, color;
	// string nombre, mensajeExplotar;
	char id, capa,capaEspecial;
protected:
	double estado, resistencia, velocidad;
	Mapa* mapa;
public:
	Vehiculo(int, int, char);
	// ~Vehiculo();
	// Vehiculo();
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	virtual void avanzar(Mapa*)const=0;
	void chocar(Vehiculo*);
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	void explotar();
	bool estaVivo();
	char obtenerId();
};