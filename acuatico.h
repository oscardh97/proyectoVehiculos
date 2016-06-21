#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
class Acuatico : public Vehiculo{
public:
	Acuatico(int, int, char, int, int, int);
	void avanzar(vector<int*>, Mapa*);
	bool puedeSeguir(const int,const int, Mapa*);
};