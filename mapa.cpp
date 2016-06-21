#include "vehiculo.h"
#include "terrestre.h"
#include "acuatico.h"
#include "mapa.h"
#include <cstddef>
#include <vector>
#include <ncurses.h>
#include <string>
#include <sstream>
using namespace std;
Mapa::Mapa(int corrienteAgua):corrienteAgua(corrienteAgua){
	this->iniciarMapa();
}
Mapa::~Mapa(){
	// for (int i = 0; i < this->vehiculos.size(); i++)
	// 	delete this->vehiculos[i];
}
int Mapa::obtenerCorriente() {
	return this->corrienteAgua;
}
Vehiculo* Mapa::obtenerVehiculo(const char id)const{
	for (int i = 0; i < this->vehiculos.size(); i++)
		if (this->vehiculos[i]->obtenerId() == id)
			return this->vehiculos[i];
	return NULL;
				
}
void Mapa::modificarCasilla(const int newX, const int newY, const char id){
	int* antPosicion = posicionVehiculo(id);
	this->mapaCaracteres[antPosicion[1]][antPosicion[0]] = this->mapaOriginal[antPosicion[1]][antPosicion[0]];
	this->mapaCaracteres[newY][newX] = id;
	// imprimirMapa();
}
char Mapa::obtenerCasilla(const int x, const int y)const{
	return mapaCaracteres[y][x];
}
char Mapa::obtenerCasillaOriginal(const int x, const int y)const{
	return this->mapaOriginal[y][x];
}
int* Mapa::posicionVehiculo(const char id)const{
	int* posicion = new int[2];
	Vehiculo* seleccionado = obtenerVehiculo(id);
	if (seleccionado->estaChocado()) {
		posicion[0] = -1;
		posicion[1] = -1;
		return posicion;
	}
	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++)
			if (mapaCaracteres[FILAS][COLUMNAS] == id) {
				posicion[0] = COLUMNAS;
				posicion[1] = FILAS;
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
		"                              ",
		"                              ",
		"     CCCCCCPCCCCCCPCCCCCC     ",
		"   | CCCCCCPCCCCCCPCCCCCC |   ",
		"   |CCC-CC    PP    CC-CCC|   ",
		"   | CC-CC    PP    CC-CC |   ",
		"     CCCCCCPCCCCCCPCCCCCC     ",
		"     CCCCCCPCCCCCCPCCCCCC     ",
		"   | CC-CC    PP    CC-CC |   ",
		"   |CCC-CC    PP    CC-CCC|   ",
		"   | CCCCCCPCCCCCCPCCCCCC |   ",
		"     CCCCCCPCCCCCCPCCCCCC     ",
		"                              ",
		"                              ",
	};

	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++){
			this->mapaCaracteres[FILAS][COLUMNAS] = mapaOriginal[FILAS][COLUMNAS];
			this->mapaOriginal[FILAS][COLUMNAS] = mapaOriginal[FILAS][COLUMNAS];
		}
}

int* Mapa::obtenerParqueo() {

	for (int FILAS = 0; FILAS < this->filas; FILAS++)
		for (int COLUMNAS = 0; COLUMNAS < this->columnas; COLUMNAS++){
			if (this->mapaCaracteres[FILAS][COLUMNAS] == '|') {
				int* coordenadas = new int[2];
				coordenadas[0] = COLUMNAS;
				coordenadas[1] = FILAS;
				return coordenadas;
			}
		}
}
int* Mapa::obtenerTotales() {
	int* totales = new int[4];
	//TOTAL VEHICULOS
	totales[0] = this->vehiculos.size();
	//TOTAL VIVOS
	totales[1] = 0;
	//TOTAL CHOCADOS
	totales[2] = 0;
	//TOTAL MUERTOS
	totales[3] = 0;
	for (int i = 0; i < this->vehiculos.size(); i++) {
		if (this->vehiculos[i]->estaVivo()) {
			totales[1]++;
		} else {
			totales[3]++;
		}
		if (this->vehiculos[i]->estaChocado()) {
			totales[2]++;
		}
	}
	return totales;
}


string Mapa::toString() {
	stringstream ss;
	for (int i = 0; i < vehiculos.size(); i++){
		int* posicion = posicionVehiculo(vehiculos[i]->obtenerId());
		ss << vehiculos[i]->toString() << "," << posicion[0] << "," << posicion[1] << ";";
	}
	return ss.str();
}