#include "vehiculo.h"
#include "terrestre.h"
#include "mapa.h"
#include <vector>
#include <cstddef>
#include <ncurses.h>
#include <thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
#include <string>
#include <sstream>
using namespace std;

Terrestre::Terrestre(char id, int resistencia, int velocidad, int color):Vehiculo(id, resistencia, velocidad, color){
	// this->vive = true;-
}	
void Terrestre::avanzar(vector<int*> coordenadas, Mapa* ciudad){
	for (int i = 0; i < coordenadas.size(); i++) {
		int* posicion = ciudad->posicionVehiculo(this->obtenerId());
		int newX = posicion[0], newY = posicion[1];
		//NORTE
		if (coordenadas[i][0] == 0) {
			for (int k = coordenadas[i][1]; k > 0 ; k--) {
				newY--;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//SUR
		} else if (coordenadas[i][0] == 1) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newY++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//ESTE
		} else if (coordenadas[i][0] == 2) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newX++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//OESTE	
		} else if (coordenadas[i][0] == 3) {
			for (int k = coordenadas[i][1]; k > 0 ; k--) {
				newX--;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		}
	}
}

bool Terrestre::puedeSeguir(const int newX,const int newY, Mapa* ciudad){
	char nuevaCasilla = ciudad->obtenerCasilla(newX, newY);
	if (nuevaCasilla != 'C' && nuevaCasilla != 'P' && nuevaCasilla != '|') {
		if (ciudad->obtenerVehiculo(nuevaCasilla) != NULL){
			this->chocar(ciudad->obtenerVehiculo(nuevaCasilla));
		} else {
			ciudad->modificarCasilla(newX, newY, this->obtenerId());
			this->explotar();
			return false;
		}
		if (nuevaCasilla == ' ')
			ciudad->modificarCasilla(newX, newY, this->obtenerId());
		// ciudad->imprimirMapa();
		return false;
	}
	ciudad->modificarCasilla(newX, newY, this->obtenerId());
	return true;
}

string Terrestre::toString() {
	stringstream ss;
	ss << "T," << Vehiculo::toString();
	return ss.str();
}