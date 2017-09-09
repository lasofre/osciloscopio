#################################################
#	Make file de osciloscopio digital	#
#	Proyecto final de informatica 2		#
#-Integrantes: Ignacio Rodriguez grandi.	#
#	      Matias Bucca.			#
#-Curso : 2R1					#
#-Carrera. Ingenieria electronica.		#
#################################################
Osii:	 comunicacion.o main.o
	gcc -o Osii  comunicacion.o main.o -lX11
Osciloscopio_2.o: main.c
	gcc -c main.c -lX11

comuncacion.o: comunicacion.c
	gcc -c comunicacion.c
clear:
	rm  *.o Osii
