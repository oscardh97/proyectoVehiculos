#include <ncurses.h>
#include "vehiculo.h"
#include "mapa.h"
void imprimirMapa(Mapa*);
int main(int argc, char const *argv[]){
	/* code */
	Mapa* ciudad = new Mapa();
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_GREEN);
	init_pair(3,COLOR_WHITE,COLOR_BLUE);
	init_pair(4,COLOR_WHITE,COLOR_BLACK);
	init_pair(5,COLOR_WHITE,166);
		imprimirMapa(ciudad);
	while (true){
		imprimirMapa(ciudad);
		refresh();
	}
	return 0;
}
void imprimirMapa(Mapa* ciudad) {
	move(0, 0);
	for (int FILAS = 0; FILAS < ciudad->obtenerFilas(); FILAS++) {
		for (int COLUMNAS = 0; COLUMNAS < ciudad->obtenerColumnas(); COLUMNAS++) {
			for(int i = 0; i < 2; i++){
				move(FILAS * 2 + i, COLUMNAS * 4);
				char casilla = ciudad->obtenerCasilla(COLUMNAS, FILAS);
				if (casilla == 'C') {
					attrset (COLOR_PAIR(1));
				} else if (casilla == '-'){
					attrset (COLOR_PAIR(2));
				} else if (casilla == ' '){
					attrset (COLOR_PAIR(3));
				} else if (casilla == 'P'){
					attrset (COLOR_PAIR(5));
				}
				// if(matriz[FILA][COLUMNA].estaViva()){
					// if(matriz[FILA][COLUMNA].esNegra()){
					// 	attrset (COLOR_PAIR(3));
					// }
					printw("%c%c%c%c", casilla, casilla, casilla, casilla);
				// }else{					
				// 	printw("       ");
				// }
			}
		}
	}
}