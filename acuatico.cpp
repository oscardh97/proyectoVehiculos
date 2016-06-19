#include "vehiculo.h"
#include "acuatico.h"
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
using namespace std;

Acuatico::Acuatico(int posX, int posY, char id, int resistencia, int velocidad):Vehiculo(posX, posY, id, resistencia, velocidad){
}	
void Acuatico::avanzar(vector<int*> coordenadas, Mapa* ciudad){
	for (int i = 0; i < coordenadas.size(); i++) {
		int* posicion = ciudad->posicionVehiculo(this->obtenerId());
		int newX = posicion[0], newY = posicion[1];
		//NORTE
		if (coordenadas[i][0] == 0) {
			for (int k = coordenadas[i][1]; k >= 0 ; k--) {
				newY--;
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
				std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->velocidad) + 100 * ciudad->obtenerCorriente()));
			}
		//SUR
		} else if (coordenadas[i][0] == 1) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newY++;
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
				std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->velocidad) + 100 * ciudad->obtenerCorriente()));
			}
		//ESTE
		} else if (coordenadas[i][0] == 2) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newX++;
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
				std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->velocidad) + 100 * ciudad->obtenerCorriente()));
			}
		//OESTE	
		} else if (coordenadas[i][0] == 3) {
			for (int k = coordenadas[i][1]; k >= 0 ; k--) {
				newX--;
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
				std::this_thread::sleep_for(std::chrono::milliseconds((1000 / this->velocidad) + 100 * ciudad->obtenerCorriente()));
			}
		}
	}
}

bool Acuatico::puedeSeguir(const int newX,const int newY, Mapa* ciudad){
	char nuevaCasilla = ciudad->obtenerCasilla(newX, newY);
	char casillaOriginal = ciudad->obtenerCasilla(newX, newY);
	ciudad->modificarCasilla(newX, newY, this->obtenerId());
	if (nuevaCasilla != ' ' && nuevaCasilla != 'P') {
		Vehiculo* otroVehiculo = ciudad->obtenerVehiculo(nuevaCasilla);
		if (otroVehiculo != NULL) {
			if (typeid(*otroVehiculo) == typeid(Acuatico)){
				this->chocar(otroVehiculo);
			} else {
				return true;
			}
		} else {
			this->explotar();
		}
		ciudad->imprimirMapa();
		return false;
	}
	return true;
}