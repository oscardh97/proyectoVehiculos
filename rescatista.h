#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
#include <string>
#include <sstream>
class Rescatista : public Vehiculo{
public:
	Rescatista(int, int, char);
	Rescatista(int, int, char, int, int, int);
	void avanzar(vector<int*>, Mapa*);
	bool puedeSeguir(const int,const int, Mapa*);
	void repararVehiculo(const int,const int, Mapa*);
	string toString();
};