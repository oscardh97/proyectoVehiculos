#pragma once
class vehiculo{
	// int posX, posY, color;
	// string nombre, mensajeExplotar;
	char id, capa,capaEspecial;
protected:
	bool vive;
public:
	vehiculo(int, int, char);
	// ~vehiculo();/*/
	// int Norte, Sur, Este, Oeste, a, b;
	// bool estaVolando,estado, moverAvion;
	// virtual void accionEnAire(){}
	// virtual void avanzar();
	// void iniciarDireaccion();
	// virtual void comprobarAvanzar();
	// virtual void comprobarRetroceso();
	void explotar();
	bool estaVivo();
	char obtenerId();
};