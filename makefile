main: main.o mapa.o vehiculo.o terrestre.o
	g++ main.o vehiculo.o terrestre.o mapa.o -lncurses -o proyecto 
	
main.o:	main.cpp mapa.o vehiculo.h
	g++ -c main.cpp 

vehiculo.o:	vehiculo.cpp vehiculo.h
	g++ -c vehiculo.cpp

terrestre.o:	terrestre.cpp vehiculo.h terrestre.h
	g++ -c terrestre.cpp

mapa.o:	mapa.cpp mapa.h vehiculo.h
	g++ -c mapa.cpp