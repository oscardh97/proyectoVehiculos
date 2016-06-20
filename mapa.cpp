#include "vehiculo.h"
#include "terrestre.h"
#include "acuatico.h"
#include "mapa.h"
#include <cstddef>
#include <vector>
#include <ncurses.h>
#include <thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
using namespace std;
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

void Mapa::imprimirMapa() {
	//CALLE
	// init_pair(1,COLOR_BLACK	,246);
	// //ARBOLES
	// init_pair(2,COLOR_WHITE,COLOR_GREEN);
	// //AGUA
	// init_pair(3,COLOR_WHITE,COLOR_BLUE);
	// //MENU
	// init_pair(4,COLOR_WHITE,COLOR_BLACK);
	// //PUENTE
	// init_pair(5,COLOR_WHITE,208);
	// //AEROPUERTO
	// init_pair(6,COLOR_WHITE,95);
	// //AEROPUERTO
	// init_pair(7,COLOR_WHITE,165);
	while(true){
		for (int FILAS = 0; FILAS < this->obtenerFilas() - 1; FILAS++) {
			attrset (COLOR_PAIR(4));
			move(FILAS * 2 + 2, 3);
			printw("%d", FILAS);
			move(FILAS * 2 + 2, 155);
			printw("%d", FILAS );
			for (int COLUMNAS = 0; COLUMNAS < this->obtenerColumnas() - 1; COLUMNAS++) {
				if (FILAS == 0) {
					attrset (COLOR_PAIR(4));
					move(1, COLUMNAS * 5 + 6);
					printw("%d",COLUMNAS);
					move(FILAS + 30, COLUMNAS * 5 + 6);
					printw("%d",COLUMNAS);
				}
				move(FILAS * 2 + 2, COLUMNAS * 5 + 5);
				char casilla = this->obtenerCasilla(COLUMNAS, FILAS);
				if (casilla == 'C') {
					attrset (COLOR_PAIR(1));
				} else if (casilla == '-') {
					attrset (COLOR_PAIR(2));
				} else if (casilla == ' ') {
					attrset (COLOR_PAIR(3));
				} else if (casilla == 'P') {
					attrset (COLOR_PAIR(5));
				} else if (casilla == '|') {
					attrset (COLOR_PAIR(6));
				} else {
					Vehiculo* actual = this->obtenerVehiculo(casilla);
					if (casilla != NULL){
						if (!actual->estaChocado()){
							attrset (COLOR_PAIR(actual->obtenerColor()));
							printw("____ ");
							move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
							printw("%s%c%s", "| ", actual->obtenerId()," \\");
						} else {
							attrset (COLOR_PAIR(8));
							printw(" \\ / ");
							move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
							printw(" / \\ ");
						}
						continue;
					}

				}
				printw("    |");
				move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
				printw("____|");

			}
		}
		move(40,80);
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}