#include "vehiculo.h"
#include "terrestre.h"
#include "mapa.h"
#include <vector>
#include <cstddef>
Terrestre::Terrestre(int posX, int posY, char id):Vehiculo(posX, posY, id){
	// this->vive = true;-
}	
void Terrestre::avanzar(vector<int*> coordenadas, Mapa* ciudad){
	int* posicion = ciudad->posicionVehiculo(this->obtenerId());
	for (int i = 0; coordenadas.size(); i++) {
		int newX = posicion[0], newY = posicion[1];
		//NORTE
		if (coordenadas[i][0] == 0) {
			newY = posicion[1] + coordenadas[i][1] + 1;
		//SUR
		} else if (coordenadas[i][0] == 1) {
			newY = posicion[1] - coordenadas[i][1] - 1;
		//ESTE
		} else if (coordenadas[i][0] == 2) {
			newX = posicion[0] + coordenadas[i][1] + 1;
		//OESTE	
		} else if (coordenadas[i][0] == 3) {
			newX = posicion[0] - coordenadas[i][1] - 1;
		}

		char nuevaCasilla = ciudad->obtenerCasilla(newX, newY);
		if (nuevaCasilla != 'C' || nuevaCasilla != 'P') {
			if (ciudad->obtenerVehiculo(nuevaCasilla) != NULL){
				this->chocar(ciudad->obtenerVehiculo(nuevaCasilla));
			} else {
				this->explotar();
			}
		}
	}
}