#include <stdio.h>
#include <iostream>
#include <string.h>
#define filas 26
#define columnas 46

using namespace std;

int x,y, totalVehiculos;
int i =1;
bool idValido;
int fill, col;
char idMover, status;
char identificadores[]={'.','X','C','P','-','|','*',' '};
int tamaArrId;
char mapaOriginal[filas][columnas];
char mapa[filas][columnas] = {
	"****************************************",
	"*                                      *",
	"*                                      *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*    CC-CC         CC         CC-CC    *",
	"* || CC-CC         PP         CC-CC || *",
	"* ||CCC-CC         CC         CC-CCC|| *",
	"* || CC-CC         CC         CC-CC || *",
	"*    CC-CC         PP         CC-CC    *",
	"*    CC-CC         CC         CC-CC    *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*    CC-CC         CC         CC-CC    *",
	"*    CC-CC         CC         CC-CC    *",
	"* || CC-CC         PP         CC-CC || *",
	"* ||CCC-CC         PP         CC-CCC|| *",
	"* || CC-CC         PP         CC-CC || *",
	"*    CC-CC         PP         CC-CC    *",
	"*    CC-CC         PP         CC-CC    *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*    CCCCCCCCCPCCCCCCCCCCPCCCCCCCCC    *",
	"*                                      *",
	"*                                      *",
	"****************************************"
};
char mapaAereo[filas][columnas] = {
	"****************************************",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"****************************************"
};
void dibujarCalle();
void crearMapaOriginal();
void validarId(char);

// void chocar();
void dibujarCalle(){
	for(int fill =0; fill < filas; fill++){
		for(int col =0; col < columnas; col++){
			cout<< mapa[fill][col];
		}
		for(int col =0; col < columnas; col++){
			cout<< mapaAereo[fill][col];
		}
		printf("\n");
	}
}
void crearMapaOriginal(){
	for(int fill =0; fill < filas; fill++){
		for(int col =0; col < columnas; col++){
			mapaOriginal[fill][col]=mapa[fill][col];
		}
	}
}
void validarId(char L){
	idValido =true;
	while(idValido==true && i<=tamaArrId){
		idValido=true;
		if(identificadores[i]==L){
			idValido=false;
		}
		i++;
	}
}

class vehiculo{
public:
	vehiculo(){
		estaVolando =false;
		moverAvion = false;
		estado = true;
		reiniciarDirecion();
	}
	~vehiculo(){}
	int Norte, Sur, Este, Oeste, a, b;
	string nombre, mensajeExplotar;
	char identificador, direccion, capa,capaEspecial;
	bool estaVolando,estado, moverAvion;
	virtual void accionEnAire(){}
	virtual void avanzar(){
		mapa[a][b]=identificador;
		reiniciarDirecion();
		dibujarCalle();
	}
	void reiniciarDirecion(){
		Norte=0;
		Sur=0;
		Oeste=0;
		Este=0;
	}
	virtual void comprobarAvanzar(){
		mapa[a][b]=mapaOriginal[a][b];
		int NS = a - Norte + Sur;
		int EO = b - Oeste + Este;
		while(identificador!='X' && a<NS){
			if(mapa[a+1][b]!=capa && mapa[a+1][b]!='P' && mapa[a+1][b]!=capaEspecial){
				identificador='X';
				// chocar();
				estado = false;
			}	
			a++;
		}
		while(identificador!='X' && b<EO){
				if(mapa[a][b+1]!=capa && mapa[a][b+1]!='P' && mapa[a][b+1]!=capaEspecial){
					identificador='X';
					estado = false;
				}	
				b++;
			}
		avanzar();
		}
	virtual void comprobarRetroceso(){
		mapa[a][b]=mapaOriginal[a][b];
		int NS = a - Norte + Sur;
		int EO = b - Oeste + Este; 
		while(identificador!='X' && a>NS){
			if(mapa[a-1][b]!=capa && mapa[a-1][b]!='P' && mapa[a-1][b]!=capaEspecial){
				identificador='X';
				estado = false;
			}	
			a--;
		}
		while(identificador!='X' && b>EO){
				if(mapa[a][b-1]!=capa && mapa[a][b-1]!='P' && mapa[a][b-1]!=capaEspecial){
					identificador='X';
					estado = false;
				}	
				b--;
			}
		avanzar();
		}	
};

class acuatico : public vehiculo{
public:
	acuatico(){
		capa=' ';
		b=1;
		a=1;
	}
	~acuatico(){}
	void avanzar(){
		if(mapa[a][b]=='P'){
			identificador='X';
			estado = false;
		}
			mapa[a][b]=identificador;
			reiniciarDirecion();
		dibujarCalle();
	}
};

class barco : public acuatico{
public:
	barco(){
		mensajeExplotar = "El barco exploto";
	}
	~barco(){}
};
class aereo : public vehiculo{
public:
	aereo(){
		a=6;
		b=2;
		capa=' ';
		estaVolando = false;
	}
	~aereo(){}
	bool puedeAterrizar;
	char accionMovimiento;
	void avanzar(){
		if(estaVolando){
			mapaAereo[a][b]=identificador;
			reiniciarDirecion();
			dibujarCalle();
		}else{
			vehiculo::avanzar();
		}
	}
	void accionEnAire(){
		printf("Desea mover, ascender o  descender? M/A/D "); cin>>accionMovimiento;
		switch(accionMovimiento){
			case 'M':
				if(estaVolando==true)volar();
				if(estaVolando==false)moverEnTierra();
				break;
			case 'A':
				ascender();
				break;
			case 'D':
				descender();
				break;
		}
		dibujarCalle();
	}
		void ascender(){
			capa='|';
			if(estaVolando==true){
				mapaAereo[a][b]=' ';
				estado = false;
				mensajeExplotar= "Se fue al espacio y " + mensajeExplotar;
			}else if(mapaAereo[a][b]!=' '){
				mapa[a][b]='X';
				estado = false;
				estaVolando = false;
				mapaAereo[a][b]=' ';
			}else{
				mapaAereo[a][b]=identificador;
				estado = true;
				estaVolando = true;
				capa = ' ';
				mapa[a][b]=mapaOriginal[a][b];
			}
		}
		void descender(){
			if(estaVolando==false){
				mapa[a][b]='X';
				mensajeExplotar =  "Hizo un hoyo en el suelo " + mensajeExplotar;
				estado = false;
			}
			autorizarAterrizaje();
			if(puedeAterrizar == true){
				mapa[a][b]=identificador;
				mapaAereo[a][b]=' ';
				estaVolando = false;
			}
		}
		virtual void autorizarAterrizaje(){
			if(mapa[a][b]!='|'){
				mapa[a][b]='X';
				estado = false;
				mapaAereo[a][b]=' ';
				puedeAterrizar=false;
			}else{
				puedeAterrizar=true;
			}
		}
		void moverEnTierra(){
			capa = '|';
		}
		
		void volar(){
			capa = ' ';
		}
	
	void comprobarAvanzar(){
		if(estaVolando == true){
			mapaAereo[a][b]=' ';
			int NS = a - Norte + Sur;
			int EO = b - Oeste + Este; 
			while(identificador!='X' && a<NS){
				if(mapaAereo[a+1][b]!=capa && mapaAereo[a+1][b]!='P'){
					identificador='X';
					estado = false;
				}	
				a++;
			}
			while(identificador!='X' && b<EO){
					if(mapaAereo[a][b+1]!=capa && mapaAereo[a][b+1]!='P'){
						identificador='X';
						estado = false;
					}	
					b++;
				}
			avanzar();
		}else{
			vehiculo::comprobarAvanzar();
		}
	}
	void comprobarRetroceso(){
		if(estaVolando == true){
			mapaAereo[a][b]=' ';
			int NS = a - Norte + Sur;
			int EO = b - Oeste + Este; 
			while(identificador!='X' && a>NS){
				if(mapaAereo[a-1][b]!=capa && mapaAereo[a-1][b]!='P'){
					identificador='X';
					estado = false;
				}	
				a--;
			}
			while(identificador!='X' && b>EO){
					if(mapaAereo[a][b-1]!=capa && mapa[a][b-1]!='P'){
						identificador='X';
						estado = false;
					}	
					b--;
				}
			avanzar();
		}else{
			vehiculo::comprobarRetroceso();
		}
	}
};
class avion : public aereo{
public:
	avion(){
		mensajeExplotar = "El avion exploto";
		moverAvion=true;
	}
	~avion(){}
};
class helicoptero : public aereo{
public:
	helicoptero(){
		mensajeExplotar = "El helicoptero exploto";
		moverAvion=false;
	}
	~helicoptero(){}
	void autorizarAterrizaje(){
		if(mapa[a][b]!='|' && mapa[a][b]!='C' && mapa[a][b]!='P'){
			mapa[a][b]='X';
			estado = false;
			mapaAereo[a][b]=' ';
			puedeAterrizar=false;
		}else{
			puedeAterrizar=true;
		}
	}
};
class terrestres : public vehiculo{
public:
	terrestres(){
		moverAvion = true;
		capa = 'C';
		a=3;
		b=7;
	}
	~terrestres(){}
};
class grua : public terrestres{
public:
	grua(){
		capaEspecial = 'X';
	}
	~grua(){}
};
class carro : public terrestres{
public:
	carro(){
		mensajeExplotar = "El carro exploto";
	}
	~carro(){}
};
class moto : public terrestres{
public:
	moto(){
		mensajeExplotar = "La moto exploto";
	}
	~moto(){}
};

void pedirDireccion(vehiculo*);
void valPedirDireccion(vehiculo*);
void pedirDatos(vehiculo*);
void pedirDireccion(vehiculo* v){
	printf("Hacia que direccion desea ir? N/S/E/O "); cin>>v->direccion;
		
		switch(v->direccion){
			case 'N':
				printf("Norte: ");cin>>v->Norte;
				v->comprobarRetroceso();
				break;
			case 'S':
				printf("Sur: ");cin>>v->Sur;
				v->comprobarAvanzar();
				break;
			case 'E':
				printf("Este: ");cin>>v->Este;
				v->comprobarAvanzar();
				break;
			case 'O':
				printf("Oeste: ");cin>>v->Oeste;
				v->comprobarRetroceso();
				break;
	}
}
void valPedirDireccion(vehiculo* v){	
	char respOtroMov;
	do{
		v->accionEnAire();
		if(v->estado==false){
			cout<< v->mensajeExplotar <<endl;
			respOtroMov = 'N';
		}else if(v->estado==true){
			pedirDireccion(v);
		
			if(v->estado==true){
				//cout<< nombreObj;
				cout<< "Desea realizar otra accion? S/N ";
				cin>> respOtroMov;
				if(respOtroMov=='N' && v->moverAvion==true && v->estaVolando==true){
					v->estado=false;
					mapaAereo[v->a][v->b]=' ';
					mapa[v->a][v->b]='X';
				}
			}
			if(v->estado==false){
				cout<< v->mensajeExplotar <<endl;
				respOtroMov = 'N';
			}			
		}
	}while(respOtroMov=='S');
}
void pedirDatos(vehiculo* v){
	printf("Ingrese el nombre: "); 
	cin>>v->nombre;
	//mapa[v->a][v->b]=mapaOriginal[v->a][v->b];
	mapa[v->a][v->b]=v->identificador;	
 	dibujarCalle();
	valPedirDireccion(v);
}

vehiculo* instancias[]={};
// void chocar(){
// 	i=9;
// 	validarId(mapa[a+1][b]);
// 	if(idValido==false){
// 		prueba = instancias[i-9];
// 		prueba->~vehiculo();
// 	}

// }
main() {
	tamaArrId=sizeof(identificadores)/sizeof(identificadores[0]);
	int tamaArrInst = 1;	
	x=0;
	y=0;	
	int tipo;
	char id;
	vehiculo* buscar;
	char nombreObj;
	crearMapaOriginal();
	dibujarCalle();
	do{
		cout<< "Que desea hacer?"<<endl;
		cout<<"1. Ingresar vehiculo" <<endl;
		cout<<"2. Modificar posicion"<<endl;
		cout<<"3. Salir"<<endl;
		cin>>status;
		if(status=='1'){	
			printf("Ingrese el tipo vehiculo: \n");
			char tiposCarros[6][100]= {"Carro","Moto","Barco","Avion","Helicoptero","Grua"};
			for(int a =0;a<=5;a++){
				cout<<a+1;
				cout<<". ";
				cout<< tiposCarros[a]<<endl;
			}
			cin>>tipo;
			
			do{
				idValido = true;
				printf("Ingrese el identificador: "); cin>>id;
				i=1;
				validarId(id);
			}while(idValido == false);
			tamaArrId++;
			identificadores[tamaArrId]=id;
		//	nombreObj = identificadores[tamaArrId];
		//	cout<< nombreOb;
			if(tipo==1){
				carro* carroN = new carro();
				instancias[tamaArrInst++]=carroN;
				carroN->identificador=id;
				pedirDatos(carroN);
			}else if(tipo==2){
				moto* motoN = new moto();
				instancias[tamaArrInst+1]=motoN;
				motoN->identificador=id;
				pedirDatos(motoN);
			}
			else if(tipo==3){
				barco* barcoN = new barco();
				instancias[tamaArrInst+1]=barcoN;
				barcoN->identificador=id;
				pedirDatos(barcoN);
			}else if(tipo==4){
				avion* avionN = new avion();
				instancias[tamaArrInst+1]=avionN;
				avionN->identificador=id;
				pedirDatos(avionN);
			}else if(tipo==5){
				helicoptero* helicopteroN = new helicoptero;
				instancias[tamaArrInst+1]=helicopteroN;
				helicopteroN->identificador=id;
				pedirDatos(helicopteroN);
			}else if(tipo==6){
				grua* gruaN = new grua;
				instancias[tamaArrInst+1]=gruaN;
				gruaN->identificador=id;
				pedirDatos(gruaN);
			}
		}
		else if(status=='2'){
			cout<< "Ingrese el identificador del vehiculo: ";
			cin>> idMover;
			i=9;
			validarId(idMover);
			if(idValido==false){
				cout<<i;
				buscar = instancias[i-9];
				valPedirDireccion(buscar);
			}
			status='1';
			
		}
	}while(status=='1');		
}
