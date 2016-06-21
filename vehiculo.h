#pragma once
#include "mapa.h"
#include <string>
#include <sstream>
class Vehiculo{
	// int posX, posY, color;
	// string nombre, mensajeExplotar;
	char id, capa,capaEspecial;
	int color;
protected:
	int estado, resistencia, velocidad;
	bool chocado;
	Mapa* mapa;
public:
	Vehiculo(int, int, char, int, int, int);
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
	void reparar();
	int estaVivo();
	int obtenerColor();
	int obtenerResistencia();
	int obtenerVelocidad();
	bool estaChocado();
	virtual bool puedeSeguir(const int,const int, Mapa*) = 0;
	char obtenerId();
	virtual string toString();
};