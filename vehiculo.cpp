// #include "mapa.h"
#include "vehiculo.h"
#include <cmath>
#include <string>
#include <sstream>
// Vehiculo::Vehiculo(){}
Vehiculo::Vehiculo(char id, int resistencia, int velocidad, int color):id(id), resistencia(resistencia), velocidad(velocidad), color(color){
	estado = 100;
	chocado = false;
	// estaVolando =false;
	// moverAvion = false;
	// estado = true;
	// reiniciarDirecion();
}
Vehiculo::~Vehiculo(){}
// void Vehiculo::avanzar(){}
char Vehiculo::obtenerId(){
	return this->id;
}
void Vehiculo::explotar(){
	this->estado = 0;
	this->chocado = true;
}
void Vehiculo::reparar(){
	this->chocado = false;
}
void Vehiculo::setEstado(int newEstado){
	this->estado = newEstado;
	// this->chocado = false;
}
int Vehiculo::estaVivo(){
	return this->estado;
}
void Vehiculo::chocar(Vehiculo* otroVehiculo) {
	double impacto = abs(this->resistencia - otroVehiculo->resistencia) / this->velocidad;

	if (impacto > this->resistencia) {
		this->estado = 0;
	} else { 
		this->estado -= abs(this->estado - abs(this->resistencia - impacto));
	}

	if (impacto > otroVehiculo->resistencia) {
		otroVehiculo->estado = 0;
	} else {
		otroVehiculo->estado -= abs(otroVehiculo->estado - abs(otroVehiculo->resistencia - impacto));
	}
	this->chocado = true;
	otroVehiculo->chocado = true;
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

string Vehiculo::toString() {
	stringstream ss;
	// int* posicion = ciudad->posicionVehiculo(id);
	ss << this->id << "," << this->resistencia << "," << this->velocidad << "," << color << "," << estado;
	return ss.str();
}