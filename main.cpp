#include <ncurses.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <cstddef>
#include "vehiculo.h"
#include "terrestre.h"
#include "acuatico.h"
#include "mapa.h"
#include <thread>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
using namespace std;
// void imprimirMapa(Mapa*);
void imprimirMenu();
void iniciarColores();
int pedirDatos(char* , bool);
void imprimirMensaje(char mensaje[]);
vector<int*> pedirCoordenadas();
int main(int argc, char const *argv[]){
	/* code */
	initscr();
	start_color();
	iniciarColores();
	char mensaje[] = "Ingrese la corriente del agua";
	char input[100];
	imprimirMensaje(mensaje);
	int corrienteAgua = pedirDatos(input, true);
	Mapa* ciudad = new Mapa(corrienteAgua);
	vector <int*> coordenadas;
	vector <thread*> hilos;
	//
		// imprimirMapa(ciudad);
	imprimirMenu();
	strcpy(mensaje, "Ingrese una opcion del menu");
	imprimirMensaje(mensaje);
	ciudad->imprimirMapa();
	while (true){
		// imprimirMapa(ciudad);
		int opcionMenu = pedirDatos(input, true);
		imprimirMenu();
		strcpy(mensaje, "Ingrese una opcion del menu");
		imprimirMensaje(mensaje);
		if (opcionMenu == 1) {
			strcpy(mensaje, "Ingrese la posicion en x");
			imprimirMensaje(mensaje);
			int posX = pedirDatos(input, true);
			strcpy(mensaje, "Ingrese la posicion en y");
			imprimirMensaje(mensaje);
			int posY = pedirDatos(input, true);
			strcpy(mensaje, "Ingrese la el id");
			imprimirMensaje(mensaje);
			char id = getch();
			printw("%c", id);
			strcpy(mensaje, "Ingrese la resistencia 1 - 100");
			imprimirMensaje(mensaje);
			int resistencia = pedirDatos(input, true);
			strcpy(mensaje, "Ingrese la cantidad de cuadros por segundo 1-3");
			imprimirMensaje(mensaje);
			int velocidad = pedirDatos(input, true);
			Acuatico* nuevo = new Acuatico(posX, posY, id, resistencia, velocidad);
			ciudad->agregarVehiculo(posX, posY, nuevo);
			coordenadas = pedirCoordenadas();
			// nuevo->avanzar(coordenadas, ciudad);
			hilos.push_back( new thread(&Vehiculo::avanzar, ref(nuevo),coordenadas, ciudad));
			// getch();
			// run.join();
			// pedirDatos(input, false);

		}
		refresh();
	}
	for (int i = 0; i < hilos.size(); i++)
		hilos[i]->join();
	return 0;
}
void iniciarColores() {
	//CALLE
	init_pair(1,COLOR_BLACK	,246);
	//ARBOLES
	init_pair(2,COLOR_WHITE,COLOR_GREEN);
	//AGUA
	init_pair(3,COLOR_WHITE,COLOR_BLUE);
	//MENU
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	//PUENTE
	init_pair(5,COLOR_WHITE,208);
	//AEROPUERTO
	init_pair(6,COLOR_WHITE,95);
	//AEROPUERTO
	init_pair(7,COLOR_WHITE,165);
	//MUERTO
	init_pair(8,COLOR_WHITE,COLOR_RED);
}
void imprimirMenu() {
	/**CUADROS DE EJEMPLOS**/
	move(33, 25);
	attrset (COLOR_PAIR(1));
	printw("-------CALLE-------");
	move(33, 50);
	attrset (COLOR_PAIR(3));
	printw("-------AGUA-------");
	move(33, 75);
	attrset (COLOR_PAIR(2));
	printw("-------ARBOLES-------");
	move(33, 100);
	attrset (COLOR_PAIR(5));
	printw("-------PUENTE-------");
	move(33, 125);
	attrset (COLOR_PAIR(6));
	printw("----AEROPUERTO----");
	//FIN CUADROS

	//MENU
	move(35, 5);
	attrset (COLOR_PAIR(4));
	printw("-------MENU-------");
	move(36, 5);
	printw("1.- Agregar Vehiculo");
}
void imprimirMensaje(char mensaje[]){

	attrset (COLOR_PAIR(4));
	move(35,55);
	addstr("---------------------------------------------------------------");
	move(37,49);
	for(int i = 50; i < 127	; i++){
		move(37, i);
		printw(" ");
		move(40, i);
		printw(" ");
	}
	move(37,67);
	addstr(mensaje);
	move(39,55);
	addstr("---------------------------------------------------------------");
	move(41,55);
	addstr("---------------------------------------------------------------");
	move(40,80);
	refresh();
}
int pedirDatos(char* input, bool esEntero){
	move(40,80);
	for(int i = 0; i < 100; i++){
		input[i] = -1;
	}
	int contadorTeclas = 0;
	noecho();
	char caracter = getch();
	while(caracter != '\n'){
		noecho();
		if(caracter >= 48 && caracter <= 57){
			addch(caracter);
			input[contadorTeclas] = caracter;
			contadorTeclas++;
		}
		caracter = getch();
	}
	if(esEntero){
		int valorEntero = 0;
		for(int i = 0; i < contadorTeclas; i++){
			valorEntero += (int)(input[i] - '0') * pow(10, contadorTeclas - 1 - i);
		}
		return valorEntero;
	}
	return contadorTeclas;
}
vector<int*> pedirCoordenadas() {
	vector <int*> coordenadas;
	do {
		char input[100];
		char mensaje[] = "Ingrese la direccion N/S/E/O";
		imprimirMensaje(mensaje);
		char direccion = getch();
		// pedirDatos(input, false);
		int* nuevaCoor = new int[2];
		strcpy (mensaje, "Ingrese la cantidad de posiciones");
		imprimirMensaje(mensaje);
		int cantPos = pedirDatos(input, true);
		if (direccion == 'N') {
			nuevaCoor[0] = 0;
		} else if (direccion == 'S') {
			nuevaCoor[0] = 1;
		} else if (direccion == 'E') {
			nuevaCoor[0] = 2;
		} else if (direccion == 'O') {
			nuevaCoor[0] = 3;
		}
		nuevaCoor[1] = cantPos;
		coordenadas.push_back(nuevaCoor);
		strcpy (mensaje, "Desea ingresar otra coordenada");
		imprimirMensaje(mensaje);
		char continuar = getch();
		if (continuar != 'S' && continuar != 's') {
			break;
		}
	} while(1);
	return coordenadas;
}