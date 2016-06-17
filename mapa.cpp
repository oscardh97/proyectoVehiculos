#include "vehiculo.h"
#include "mapa.h"
#include <vector>
using namespace std;
	// char[26][46] mapaCaracteres;
	// vector <vehiculo*> vehiculos;
Mapa::Mapa(){

}
Mapa::~Mapa(){
	for (int i = 0; i < vehiculos.size(); i++)
		delete vehiculos[i];
}
vehiculo* Mapa::obtenerVehiculo(const char id)const{
	for (int i = 0; i < vehiculos.size(); i++)
		if (vehiculos[i]->obtenerId() == id)
			return vehiculos[i];
				
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
	vehiculo* seleccionado = obtenerVehiculo(id);
	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++)
			if (mapaCaracteres[FILAS][COLUMNAS] == id) {
				int* posicion = new int[2];
				posicion[0] = FILAS;
				posicion[1] = COLUMNAS;
				return posicion;
			}
}
void  Mapa::agregarVehiculo(int x, int y, vehiculo& nuevoVehiculo){
	// this->vehiculos.push_back(nuevoVehiculo);
	mapaCaracteres[y][x] = nuevoVehiculo.obtenerId();
}