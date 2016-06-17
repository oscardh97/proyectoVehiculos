#pragma once
#include "vehiculo.h"
#include <vector>
using namespace std;
class Mapa{
	static const int filas = 26, columnas = 46;
	char mapaCaracteres[filas][columnas], mapaOriginal[filas][columnas];
	vector <vehiculo*> vehiculos;
	public:
		Mapa();
		~Mapa();
		vehiculo* obtenerVehiculo(const char)const;
		void modificarCasilla(const int, const int, const char);
		char obtenerCasilla(const int, const int)const;
		int* posicionVehiculo(const char)const;
		void agregarVehiculo(int, int, vehiculo&);
};