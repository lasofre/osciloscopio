# Osciloscopio Digita Inteligente OSCII	V 1.0	
## Integrandes del proyecto:
	+Ignacio Rodriguez Grandi.	|Contacto:nato1631@gmail.com
	+Matias Bucca.			|Contacto:lasofre@gmail.com

## Informacion del proyecto:

Este proyecto tiene por objetivo el desarrollo de un osciloscopio digital de bajo costo
capas de graficar señales de frecuencias medias.La finalidad del mismo es permitir 
crear una herramienta útil para la educacion.

Para poder llevar a cabo el desarrollo se utilizan herramientas libres y gratuitas que se encuentran a disposicion de todos en la web.

## Firmware:
	El firmware fue programado en el programa pinguino ide:
	 http://pinguino.cc/download.php

## Bibliotecas:

fcntl.h 		//Definiciones de control de archivos
stdio.h
stdlib.h
X11/Xlib.h		//Biblioteca grafica
unistd.h
errno.h			//Definiciones de control de errores 
sys/ioctl.h 		//Constantes para ioctl 
termios.h 		//Estructura de control termios 
string.h
unistd.h 		// close function
	
## Cambios:
### <07/09/17>
* Se cambio el archivo Osciloscopio_2.c por main.c
* Se se atualzó el Makefile.
* La funcion lectura_puerto se paso de main.c a comunicacion.c
### <14/09/17>
* Se habilitó la comunicacion con la placa.
* Se arreglaron errores en la grafica de datos.
* Se borró la funcion dib_signal por errores.
* Nueva funcion <<Chop>> con la tecla c.
###<03/11/17>
* Nueva interfaz.
* La función Parametros (P) no esta habilitada.
### Bibliografia:
#### Tutoriales X11lib:
* https://tronche.com/gui/x/xlib/
* https://www.student.cs.uwaterloo.ca/~cs349/f15/resources/X/xTutorialPart1.html
* http://math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html

