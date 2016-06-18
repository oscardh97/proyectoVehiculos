// #include "mapa.h"
#include "vehiculo.h"
// Vehiculo::Vehiculo(){}
Vehiculo::Vehiculo(int posX, int posY, char id):id(id){
	estado = true;
	// estaVolando =false;
	// moverAvion = false;
	// estado = true;
	// reiniciarDirecion();
}
// Vehiculo::~Vehiculo(){}
	// virtual void avanzar(){}
char Vehiculo::obtenerId(){
	return this->id;
}
void Vehiculo::explotar(){
	this->estado = false;
}
bool Vehiculo::estaVivo(){
	return this->estado;
}
void Vehiculo::chocar(Vehiculo* otroVehiculo) {
	double impacto = (this->resistencia + otroVehiculo->resistencia) / this->velocidad * 10;
	this->estado -= impacto;
	otroVehiculo->estado -= impacto;

	if (this->estado <= 0) {
		this->explotar();
	}
	if (otroVehiculo->estado <= 0) {
		otroVehiculo->explotar();
	}
}