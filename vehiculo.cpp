// #include "mapa.h"
#include "vehiculo.h"
#include <cmath>
// Vehiculo::Vehiculo(){}
Vehiculo::Vehiculo(int posX, int posY, char id, int resistencia, int velocidad, int color):id(id), resistencia(resistencia), velocidad(velocidad), color(color){
	estado = 100;
	chocado = false;
	// estaVolando =false;
	// moverAvion = false;
	// estado = true;
	// reiniciarDirecion();
}
// Vehiculo::~Vehiculo(){}
// void Vehiculo::avanzar(){}
char Vehiculo::obtenerId(){
	return this->id;
}
void Vehiculo::explotar(){
	this->estado = 0;
}
int Vehiculo::estaVivo(){
	return this->estado;
}
void Vehiculo::chocar(Vehiculo* otroVehiculo) {
	double impacto = abs(this->resistencia - otroVehiculo->resistencia) / this->velocidad;
	this->estado -= (this->estado - abs(this->resistencia - impacto));
	otroVehiculo->estado -= (otroVehiculo->estado - abs(otroVehiculo->resistencia - impacto));
	this->chocado = true;
	otroVehiculo->chocado = true;
	if (this->estado <= 0) {
		this->explotar();
	}
	if (otroVehiculo->estado <= 0) {
		otroVehiculo->explotar();
	}
}

int Vehiculo::obtenerColor() {
	return this->color;
}
int Vehiculo::obtenerResistencia(){
	return this->resistencia;
}
int Vehiculo::obtenerVelocidad(){
	return this->velocidad;
}

bool Vehiculo::estaChocado(){
	return this->chocado;
}
