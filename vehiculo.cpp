#include "vehiculo.h"
vehiculo::vehiculo(int posX, int posY, char id):id(id){
	this->vive = true;
	// estaVolando =false;
	// moverAvion = false;
	// estado = true;
	// reiniciarDirecion();
}
// vehiculo::~vehiculo(){}
	// virtual void avanzar(){}
	char vehiculo::obtenerId(){
		return this->id;
	}
	void vehiculo::explotar(){
		this->vive = false;
	}
	bool vehiculo::estaVivo(){
		return this->vive;
	}
	// virtual void comprobarAvanzar(char[26][] mapa, int newX, int newY){
	// 	while(estado && a<NS){
	// 		if(mapa[a+1][b]!=capa && mapa[a+1][b]!='P' && mapa[a+1][b]!=capaEspecial){
	// 			identificador =' X';
	// 			// chocar();
	// 			estado = false;
	// 		}	
	// 		a++;
	// 	}
	// 	while(identificador!='X' && b<EO){
	// 			if(mapa[a][b+1]!=capa && mapa[a][b+1]!='P' && mapa[a][b+1]!=capaEspecial){
	// 				identificador='X';
	// 				estado = false;
	// 			}	
	// 			b++;
	// 		}
	// 	avanzar();
	// 	}
	// virtual void comprobarRetroceso(){
	// 	mapa[a][b]=mapaOriginal[a][b];
	// 	int NS = a - Norte + Sur;
	// 	int EO = b - Oeste + Este; 
	// 	while(identificador!='X' && a>NS){
	// 		if(mapa[a-1][b]!=capa && mapa[a-1][b]!='P' && mapa[a-1][b]!=capaEspecial){
	// 			identificador='X';
	// 			estado = false;
	// 		}	
	// 		a--;
	// 	}
	// 	while(identificador!='X' && b>EO){
	// 			if(mapa[a][b-1]!=capa && mapa[a][b-1]!='P' && mapa[a][b-1]!=capaEspecial){
	// 				identificador='X';
	// 				estado = false;
	// 			}	
	// 			b--;
	// 		}
	// 	avanzar();
	// 	}	
// };