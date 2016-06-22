#pragma once
#include "mapa.h"
#include <string>
#include <sstream>
class Vehiculo{
	char id, capa,capaEspecial;
	int color;
protected:
	int estado, resistencia, velocidad;
	bool chocado;
	Mapa* mapa;
public:
	Vehiculo(char, int, int, int);
	~Vehiculo();
	virtual void avanzar(vector<int*>, Mapa*) = 0;
	void chocar(Vehiculo*);
	void explotar();
	void reparar();
	int estaVivo();
	int obtenerColor();
	int obtenerResistencia();
	void setEstado(int);
	int obtenerVelocidad();
	bool estaChocado();
	virtual bool puedeSeguir(const int,const int, Mapa*) = 0;
	char obtenerId();
	virtual string toString();
};