#include "vehiculo.h"
#include "rescatista.h"
#include "mapa.h"
#include <vector>
#include <cstddef>
#include <ncurses.h>
#include <typeinfo>
#include <thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
#include <string>
#include <sstream>
using namespace std;

Rescatista::Rescatista(char id):Vehiculo(id, 100, 1, 12){
}

Rescatista::Rescatista(char id, int resistencia, int velocidad, int color):Vehiculo(id, resistencia, velocidad, color){
}
void Rescatista::avanzar(vector<int*> coordenadas, Mapa* ciudad){
	for (int i = 0; i < coordenadas.size(); i++) {
		int* posicion = ciudad->posicionVehiculo(this->obtenerId());
		int newX = posicion[0], newY = posicion[1];
		//NORTE
		if (coordenadas[i][0] == 0) {
			for (int k = coordenadas[i][1]; k > 0 ; k--) {
				newY--;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (newY == -1){
					newY = ciudad->obtenerFilas() - 2;
				}
				this->repararVehiculo(newX, newY, ciudad);
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//SUR
		} else if (coordenadas[i][0] == 1) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newY++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (newY == ciudad->obtenerFilas() - 1){
					newY =  0;
				}
				this->repararVehiculo(newX, newY, ciudad);
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//ESTE
		} else if (coordenadas[i][0] == 2) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newX++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (newX == ciudad->obtenerColumnas() - 1){
					newX =  0;
				}
				this->repararVehiculo(newX, newY, ciudad);
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//OESTE	
		} else if (coordenadas[i][0] == 3) {
			for (int k = coordenadas[i][1]; k > 0 ; k--) {
				newX--;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * this->velocidad));
				if (newX == -1){
					newX = ciudad->obtenerColumnas() - 2;
				}
				this->repararVehiculo(newX, newY, ciudad);
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		}
	}
}

void Rescatista::repararVehiculo(const int newX,const int newY, Mapa* ciudad){
	char nuevaCasilla = ciudad->obtenerCasilla(newX, newY);
	Vehiculo* vehiculoChocado = ciudad->obtenerVehiculo(nuevaCasilla);
	if (vehiculoChocado != NULL) {
		if (vehiculoChocado->estaVivo()) {
			if (vehiculoChocado->estaChocado()){
				std::this_thread::sleep_for(std::chrono::milliseconds((100 - vehiculoChocado->estaVivo()) * 100));
				int* taller = ciudad->obtenerParqueo();
				ciudad->modificarCasilla(taller[0], taller[1], vehiculoChocado->obtenerId());
				vehiculoChocado->reparar();
			} else {
				this->chocar(vehiculoChocado);
			}
		}
	}
	ciudad->modificarCasilla(newX, newY, this->obtenerId());
}

bool Rescatista::puedeSeguir(const int posX,const int posY, Mapa* ciudad){
	return this->estaVivo();
}

string Rescatista::toString() {
	stringstream ss;
	ss << "R," << Vehiculo::toString();
	return ss.str();
}