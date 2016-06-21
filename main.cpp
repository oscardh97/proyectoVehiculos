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
#include <stdio.h>
using namespace std;
void imprimirMapa(Mapa*);
int imprimirMenu(int);
void iniciarColores();
int pedirDatos(char* , bool);
void imprimirMensaje(char[], bool = false);
vector<int*> pedirCoordenadas();
void imprimirInfoVehiculo(Vehiculo*, Mapa*);
void imprimirInfoMapa(Mapa*);
int main(int argc, char const *argv[]){
	/* code */
	initscr();
	start_color();
	iniciarColores();
	// int corrienteAgua = pedirDatos(input, true);
	Mapa* ciudad = new Mapa(5);
	vector <int*> coordenadas;
	vector <thread*> hilos;
	char mensaje[] = "Bienvenido presione una tecla para continuar";
	char input[100];
	imprimirMensaje(mensaje);
	refresh();
	// thread actualizador(&Mapa::imprimirMapa, ref(ciudad));
	thread actualizador(imprimirMapa, ciudad);
	// ciudad->imprimirMapa();
	getch();
	while (true){
		strcpy(mensaje, "Ingrese una opcion del menu");
		imprimirMensaje(mensaje);
		int opcionMenu = imprimirMenu(0);
		if (opcionMenu == 1) {
			strcpy(mensaje, "Ingrese el tipo de vehiculo");
			imprimirMensaje(mensaje);
			int opcionTipo = imprimirMenu(1);
			int posX, posY;
			do{
				strcpy(mensaje, "Ingrese la posicion en x");
				imprimirMensaje(mensaje);
				posX = pedirDatos(input, true);
				strcpy(mensaje, "Ingrese la posicion en y");
				imprimirMensaje(mensaje);
				posY = pedirDatos(input, true);
				char casilla = ciudad->obtenerCasilla(posX, posY); 
				if (posX < 0 || posX > ciudad->obtenerColumnas() - 2 || posY < 0 || posY > ciudad->obtenerFilas() - 2){
					strcpy(mensaje, "Casilla no valida");
					imprimirMensaje(mensaje, true);
					getch();
					continue;
				}

				if (opcionTipo == 1 && (casilla == 'C' || casilla == 'P')) {
					break;
				} else if (opcionTipo == 2 && (casilla == ' ' || casilla == 'P')){
					break;
				} else {
					strcpy(mensaje, "Casilla no valida");
					imprimirMensaje(mensaje, true);
					getch();
				}
			} while(true);
			strcpy(mensaje, "       Ingrese el id");
			imprimirMensaje(mensaje);
			char id = getch();
			printw("%c", id);
			strcpy(mensaje, "Ingrese la resistencia 1 - 100");
			imprimirMensaje(mensaje);
			int resistencia = pedirDatos(input, true);
			strcpy(mensaje, "Ingrese la cantidad de cuadros por segundo 1-3");
			imprimirMensaje(mensaje);
			int velocidad = pedirDatos(input, true);
			strcpy(mensaje, "Ingrese el color");
			imprimirMensaje(mensaje);
			int color = imprimirMenu(2);
			Vehiculo* nuevo;
			if (opcionTipo == 1){
				nuevo = new Terrestre(posX, posY, id, resistencia, velocidad, color);
			} else if (opcionTipo == 2) {
				nuevo = new Acuatico(posX, posY, id, resistencia, velocidad, color);
			}
			ciudad->agregarVehiculo(posX, posY, nuevo);
			coordenadas = pedirCoordenadas();
			hilos.push_back( new thread(&Vehiculo::avanzar, ref(nuevo),coordenadas, ciudad));
		} else if(opcionMenu == 2) {
			strcpy(mensaje, "       Ingrese el id");
			imprimirMensaje(mensaje);
			char id = getch();
			printw("%c", id);
			Vehiculo* seleccionado = ciudad->obtenerVehiculo(id);
			if (seleccionado != NULL) {
				if (seleccionado->estaVivo()){
					coordenadas = pedirCoordenadas();
					hilos.push_back( new thread(&Vehiculo::avanzar, ref(seleccionado),coordenadas, ciudad));
				} else {
					strcpy(mensaje, "El vehiculo esta destrozado");
					imprimirMensaje(mensaje);
					getch();
				}
			} else {
				strcpy(mensaje, "El vehiculo no existe");
				imprimirMensaje(mensaje, true);
				getch();
			}
		} else if(opcionMenu == 3) {
			strcpy(mensaje, "       Ingrese el id");
			imprimirMensaje(mensaje);
			char id = getch();
			printw("%c", id);
			Vehiculo* seleccionado = ciudad->obtenerVehiculo(id);
			if (seleccionado != NULL) {
				imprimirInfoVehiculo(seleccionado, ciudad);
			} else {
				strcpy(mensaje, "El vehiculo no existe");
				imprimirMensaje(mensaje, true);
				getch();
			}
		} else if(opcionMenu == 4) {
			imprimirInfoMapa(ciudad);
		} else if(opcionMenu == 6) {
			break;
		} else { 
			strcpy(mensaje, "Opcion invalida");
			imprimirMensaje(mensaje, true);
			getch();
		}
		// refresh();
	}
	for (int i = 0; i < hilos.size(); i++)
		hilos[i]->detach();
	actualizador.detach();
    endwin();
    exit(1);
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
	//ROSADO
	init_pair(7,COLOR_WHITE,165);
	//MUERTO
	init_pair(8,COLOR_WHITE,COLOR_RED);
	//AMARILLO
	init_pair(9,COLOR_BLACK,226);
	//MORADO
	init_pair(10,COLOR_WHITE,54);
	//AZUL
	init_pair(11,COLOR_WHITE,17);
}
int imprimirMenu(int opcion) {
	/**CUADROS DE EJEMPLOS**/
	move(33, 25);
	attrset (COLOR_PAIR(1));
	printw("-------CALLE-------");
	move(33, 50);
	attrset (COLOR_PAIR(3));
	printw("-------AGUA-------");
	move(33, 75);
	attrset (COLOR_PAIR(2));
	printw("-------ARBOLES-----");
	move(33, 100);
	attrset (COLOR_PAIR(5));
	printw("-------PUENTE-----");
	move(33, 125);
	attrset (COLOR_PAIR(6));
	printw("----AEROPUERTO----");
	//FIN CUADROS

	char input[100];
	//MENU
	if (opcion == 0) {
		move(35, 5);
		attrset (COLOR_PAIR(4));
		printw("-------MENU-------");
		move(36, 5);
		printw("1.- Agregar Vehiculo    ");
		move(37, 5);
		printw("2.- Modificar posicion  ");
		move(38, 5);
		printw("3.- Informacion vehiculo");
		move(39, 5);
		printw("4.- Informacion mapa    ");
		move(40, 5);
		printw("5.- Guardar             ");
		move(41, 5);
		printw("6.- Salir    ");
	} else if (opcion == 1) {
		move(35, 5);
		attrset (COLOR_PAIR(4));
		printw("-------TIPO-------");
		move(36, 5);
		printw("1.- Terrestre         ");
		move(37, 5);
		printw("2.- Acuatico          ");
		move(38, 5);
		printw("3.- Aereo              ");
	} else if (opcion == 2) {
		move(35, 5);
		attrset (COLOR_PAIR(4));
		printw("-------COLORES-------");
		attrset (COLOR_PAIR(11));
		move(36, 5);
		printw("1.-       AZUL         ");
		attrset (COLOR_PAIR(9));
		move(37, 5);
		printw("2.-     AMARILLO       ");
		attrset (COLOR_PAIR(10));
		move(38, 5);
		printw("3.-      MORADO       ");
		attrset (COLOR_PAIR(7));
		move(39, 5);
		printw("4.-      ROSADO        ");

		int color = pedirDatos(input, true);

		if (color == 1)
			return 11;
		else if (color == 2)
			return 9;
		else if (color == 3)
			return 10;
		else
			return 7;
	}
	return pedirDatos(input, true);
}
void imprimirMensaje(char mensaje[], bool esError){
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
	if (esError)
		attrset (COLOR_PAIR(8));
	else
		attrset (COLOR_PAIR(4));
	addstr(mensaje);
	attrset (COLOR_PAIR(4));
	move(39,55);
	addstr("---------------------------------------------------------------");
	move(41,55);
	addstr("---------------------------------------------------------------");
	move(40,80);
	// refresh();
}
void imprimirInfoVehiculo(Vehiculo* seleccionado, Mapa* ciudad) {
	if (seleccionado != NULL) {
		move(35, 140);
		attrset (COLOR_PAIR(4));
		printw("------VEHICULO-------");
		move(36, 140);
		printw("%s%c","ID = ", seleccionado->obtenerId());
		move(37, 140);
		printw("%s%d%s","Estado = ", seleccionado->estaVivo(), "    ");
		move(38, 140);
		printw("%s%d%s","Velocidad = ", seleccionado->obtenerVelocidad(), "    ");
		move(40, 140);
		printw("%s%d%s","Resistencia = ", seleccionado->obtenerResistencia(), "    ");
		move(41, 140);

		int* posicion = ciudad->posicionVehiculo(seleccionado->obtenerId());
		printw("%s%d%s%d%c","Posicion = (", posicion[0], ", ", posicion[1], ')');
		// printw("4.- Informacion mapa    ");
	}
}
void imprimirInfoMapa(Mapa* ciudad) {
	int* totales = ciudad->obtenerTotales();
	move(35, 140);
	attrset (COLOR_PAIR(4));
	printw("--------CIUDAD-------");
	move(36, 140);
	printw("%s%d","VIVOS    = ", totales[1]);
	move(37, 140);
	printw("%s%d%s","CHOCADOS = ", totales[2], "    ");
	move(38, 140);
	printw("%s%d%s","MUERTOS  = ", totales[3], "    ");
	move(40, 140);
	printw("%s%d%s","TOTAL    = ", totales[0], "    ");
	move(41, 140);
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
		if (direccion == 'N' || direccion == 'n') {
			nuevaCoor[0] = 0;
		} else if (direccion == 'S' || direccion == 's') {
			nuevaCoor[0] = 1;
		} else if (direccion == 'E' || direccion == 'e') {
			nuevaCoor[0] = 2;
		} else if (direccion == 'O' || direccion == 'o') {
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

void imprimirMapa(Mapa* ciudad) {
	while(true){
		for (int FILAS = 0; FILAS < ciudad->obtenerFilas() - 1; FILAS++) {
			attrset (COLOR_PAIR(4));
			move(FILAS * 2 + 2, 3);
			printw("%d", FILAS);
			move(FILAS * 2 + 2, 155);
			printw("%d", FILAS );
			for (int COLUMNAS = 0; COLUMNAS < ciudad->obtenerColumnas() - 1; COLUMNAS++) {
				if (FILAS == 0) {
					attrset (COLOR_PAIR(4));
					move(1, COLUMNAS * 5 + 6);
					printw("%d",COLUMNAS);
					move(FILAS + 30, COLUMNAS * 5 + 6);
					printw("%d",COLUMNAS);
				}
				move(FILAS * 2 + 2, COLUMNAS * 5 + 5);
				char casilla = ciudad->obtenerCasilla(COLUMNAS, FILAS);
				if (casilla == 'C') {
					attrset (COLOR_PAIR(1));
				} else if (casilla == '-') {
					attrset (COLOR_PAIR(2));
				} else if (casilla == ' ') {
					attrset (COLOR_PAIR(3));
				} else if (casilla == 'P') {
					attrset (COLOR_PAIR(5));
				} else if (casilla == '|') {
					attrset (COLOR_PAIR(6));
				} else {
					Vehiculo* actual = ciudad->obtenerVehiculo(casilla);
					if (casilla != NULL){
						if (!actual->estaChocado()){
							attrset (COLOR_PAIR(actual->obtenerColor()));
							printw("____ ");
							move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
							printw("%s%c%s", "| ", actual->obtenerId()," \\");
						} else {
							attrset (COLOR_PAIR(8));
							printw(" \\ / ");
							move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
							printw(" / \\ ");
						}
						continue;
					}

				}
				printw("    |");
				move(FILAS * 2 + 3, COLUMNAS * 5 + 5);
				printw("____|");

			}
		}
		move(40,80);
		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}