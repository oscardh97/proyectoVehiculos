#pragma once
// #include "vehiculo.h"
#include <vector>
using namespace std;
class Vehiculo;
class Mapa{
	static const int filas = 21, columnas = 33;
	char mapaCaracteres[filas][columnas], mapaOriginal[filas][columnas];
	vector <Vehiculo*> vehiculos;
	Vehiculo* vehiculo;
	public:
		Mapa();
		~Mapa();
		Vehiculo* obtenerVehiculo(const char)const;
		void modificarCasilla(const int, const int, const char);
		char obtenerCasilla(const int, const int)const;
		int* posicionVehiculo(const char)const;
		void agregarVehiculo(int, int, Vehiculo*);
		void iniciarMapa();
		int obtenerFilas();
		int obtenerColumnas();
};