#pragma once
// #include "vehiculo.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Vehiculo;
class Mapa{
	static const int filas = 15, columnas = 31;
	char mapaCaracteres[filas][columnas], mapaOriginal[filas][columnas];
	vector <Vehiculo*> vehiculos;
	Vehiculo* vehiculo;
	int corrienteAgua;
	public:
		Mapa(int);
		~Mapa();
		Vehiculo* obtenerVehiculo(const char)const;
		void modificarCasilla(const int, const int, const char);
		char obtenerCasilla(const int, const int)const;
		char obtenerCasillaOriginal(const int, const int)const;
		int* posicionVehiculo(const char)const;
		void agregarVehiculo(int, int, Vehiculo*);
		void iniciarMapa();
		int obtenerFilas();
		void imprimirMapa();
		int obtenerColumnas();
		int obtenerCorriente();
		int* obtenerTotales();
		int* obtenerParqueo();
		string toString();
};