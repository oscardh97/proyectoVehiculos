#pragma once
#include <vector>
#include "vehiculo.h"
#include "mapa.h"
#include <string>
#include <sstream>
class Terrestre : public Vehiculo{
public:
	Terrestre(char, int, int, int);
	void avanzar(vector<int*>, Mapa*);
	bool puedeSeguir(const int,const int, Mapa*);
	string toString();
};