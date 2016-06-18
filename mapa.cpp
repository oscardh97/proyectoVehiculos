#include "vehiculo.h"
#include "mapa.h"
#include <vector>
using namespace std;
Mapa::Mapa(){
	this->iniciarMapa();
}
Mapa::~Mapa(){
	// for (int i = 0; i < this->vehiculos.size(); i++)
	// 	delete this->vehiculos[i];
}
Vehiculo* Mapa::obtenerVehiculo(const char id)const{
	for (int i = 0; i < this->vehiculos.size(); i++)
		if (this->vehiculos[i]->obtenerId() == id)
			return this->vehiculos[i];
	// return new Vehiculo();
				
}
void Mapa::modificarCasilla(const int newX, const int newY, const char id){
	int* antPosicion = posicionVehiculo(id);
	this->mapaCaracteres[antPosicion[0]][antPosicion[1]] = this->mapaOriginal[antPosicion[0]][antPosicion[1]];
	this->mapaCaracteres[newY][newX] = id;
}
char Mapa::obtenerCasilla(const int x, const int y)const{
	return mapaCaracteres[y][x];
}
int* Mapa::posicionVehiculo(const char id)const{
	Vehiculo* seleccionado = obtenerVehiculo(id);
	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++)
			if (mapaCaracteres[FILAS][COLUMNAS] == id) {
				int* posicion = new int[2];
				posicion[0] = FILAS;
				posicion[1] = COLUMNAS;
				return posicion;
			}
}
void  Mapa::agregarVehiculo(int x, int y, Vehiculo* nuevoVehiculo){
	this->vehiculos.push_back(nuevoVehiculo);
	mapaCaracteres[y][x] = nuevoVehiculo->obtenerId();
}
int Mapa::obtenerFilas(){
	return this->filas;
}
int Mapa::obtenerColumnas() {
	return this->columnas;
}
void Mapa::iniciarMapa() {
	char mapaOriginal[this->filas][this->columnas] = {
		"                                ",
		"                                ",
		"                                ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"     CC-CC     CC     CC-CC     ",
		"  || CC-CC     PP     CC-CC ||  ",
		"  || CC-CC     PP     CC-CC ||  ",
		"     CC-CC     CC     CC-CC     ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"     CC-CC     CC     CC-CC     ",
		"  || CC-CC     PP     CC-CC ||  ",
		"  || CC-CC     PP     CC-CC ||  ",
		"     CC-CC     CC     CC-CC     ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"     CCCCCCCPCCCCCCPCCCCCCC     ",
		"                                ",
		"                                ",
		"                                "
	};

	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++)
			mapaCaracteres[FILAS][COLUMNAS] = mapaOriginal[FILAS][COLUMNAS];
}