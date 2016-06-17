proyecto:	mapa.o vehiculo.o
	g++ mapa.o vehiculo.o -o proyecto

# main.o:	main.cpp mapa.h vehiculo.h
# 	g++ -c main.cpp

mapa.o:	mapa.cpp mapa.h
	g++ -c mapa.cpp

vehiculo.o:	vehiculo.cpp vehiculo.h
	g++ -c vehiculo.cpp
