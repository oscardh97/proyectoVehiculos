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
#include <string>
#include <sstream>
using namespace std;

Acuatico::Acuatico(char id, int resistencia, int velocidad, int color):Vehiculo(id, resistencia, velocidad, color){
}
void Acuatico::avanzar(vector<int*> coordenadas, Mapa* ciudad){
	for (int i = 0; i < coordenadas.size(); i++) {
		int* posicion = ciudad->posicionVehiculo(this->obtenerId());
		int newX = posicion[0], newY = posicion[1];
		//NORTE
		if (coordenadas[i][0] == 0) {
			for (int k = coordenadas[i][1]; k >= 0 ; k--) {
				newY--;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (this->velocidad + ciudad->obtenerCorriente())));
				if (newY == -1){
					newY = ciudad->obtenerFilas() - 2;
				}
				if (!this->puedeSeguir(newX, newY, ciudad)){
					return;
				}
			}
		//SUR
		} else if (coordenadas[i][0] == 1) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newY++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (this->velocidad + ciudad->obtenerCorriente())));
				if (newY == ciudad->obtenerFilas() - 1){
					newY =  0;
				}
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//ESTE
		} else if (coordenadas[i][0] == 2) {
			for (int k = 0; k < coordenadas[i][1] ; k++) {
				newX++;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (this->velocidad + ciudad->obtenerCorriente())));
				if (newX == ciudad->obtenerColumnas() - 1){
					newX =  0;
				}
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		//OESTE	
		} else if (coordenadas[i][0] == 3) {
			for (int k = coordenadas[i][1]; k >= 0 ; k--) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * (this->velocidad + ciudad->obtenerCorriente())));
				newX--;
				if (newX == -1){
					newX = ciudad->obtenerColumnas() - 2;
				}
				if (!this->puedeSeguir(newX, newY, ciudad))
					return;
			}
		}
	}
}

bool Acuatico::puedeSeguir(const int newX,const int newY, Mapa* ciudad){
	char nuevaCasilla = ciudad->obtenerCasilla(newX, newY);
	char casillaOriginal = ciudad->obtenerCasilla(newX, newY);
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
		return false;
	}
	ciudad->modificarCasilla(newX, newY, this->obtenerId());
	return true;
}

string Acuatico::toString() {
	stringstream ss;
	ss << "A," << Vehiculo::toString();
	return ss.str();
}