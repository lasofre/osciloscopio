#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 		/* Definiciones de control de archivos */
#include <errno.h> 		/* Definiciones de control de errores */
#include <sys/ioctl.h> 	/* Constantes para ioctl */
#include <termios.h> 	/* Estructura de control termios */
#include <string.h>
#include <unistd.h> // close function
void estadolinea( char *puerto, struct termios opciones );
int iniciar_com(char puerto[]);

int iniciar_com(char puerto[]){
  int fd;
  struct termios opciones;

  fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
  if (fd == -1) {
    perror("open_port");
    exit( 1 );
  }
  else

  fcntl(fd, F_SETFL, 0); // funciona en forma síncrona
                           // con FNDELAY lo hace en forma asíncrona

  
  tcgetattr( fd, &opciones );// Estado de linea por la estructura termios

  printf( "Antes de configurar: \n" ); 
  estadolinea( puerto, opciones );
  
  cfsetispeed( &opciones, B115200 );// Fijando velocidad del puerto

  opciones.c_cflag |= (CLOCAL | CREAD);// Habilitación del receptor y modo local

  // Tamaño de palabra
  opciones.c_cflag &= ~CSIZE; /* Enmascara bits de tamaño de palabra */
  opciones.c_cflag |= CS8;    /* Selecciona 8 bits */

 
  opciones.c_cflag &= ~CSTOPB; // Esto es para fijar 1 stop bit
  
  opciones.c_cflag &= ~PARENB;// Esto es para fijar NO paridad (N)

  tcsetattr( fd, TCSANOW, &opciones );// Escritura de la configuración en el puerto

  
  tcgetattr( fd, &opciones );// Lectura de la configuración del puerto
  printf( "Después de configurar:\n" ); 
  estadolinea( puerto, opciones );
  return fd;

 }

 void estadolinea( char *puerto, struct termios opciones ) {
  int speed;

  printf( "%s: ", puerto );
  // Bits de cada palabra
  if( (opciones.c_cflag & CSIZE) == CS5) printf( "5" );
  if( (opciones.c_cflag & CSIZE) == CS6) printf( "6" );
  if( (opciones.c_cflag & CSIZE) == CS7) printf( "7" );
  if( (opciones.c_cflag & CSIZE) == CS8) printf( "8" );

  // Paridad
  if( (opciones.c_cflag & PARENB) == 0) printf( "N" );
  else {
    if( (opciones.c_cflag & PARODD) == PARODD) printf( "O" );
    else printf( "E" );  // paridad par
  }

  // Bits de parada
  if( (opciones.c_cflag & CSTOPB) == CSTOPB) printf( "2" );
  else printf( "1" );

  // Velocidad de transmisión
  printf( " " );
  speed = cfgetispeed( &opciones ); 
  switch( speed ) {
    case B50: printf( "50" ); break;
    case B75: printf( "75" ); break;
    case B110: printf( "110" ); break;
    case B134: printf( "134" ); break;
    case B150: printf( "150" ); break;
    case B200: printf( "200" ); break;
    case B300: printf( "300" ); break;
    case B600: printf( "600" ); break;
    case B1200: printf( "1200" ); break;
    case B1800: printf( "1800" ); break;
    case B2400: printf( "2400" ); break;
    case B4800: printf( "4800" ); break;
    case B9600: printf( "9600" ); break;
    case B19200: printf( "19200" ); break;
    case B38400: printf( "38400" ); break;
    case B57600: printf( "57600" ); break;
    case B115200: printf( "115200" ); break;
    default: printf ( "Error" ); break;
  }
  printf( " bps\n" );
}

int lectura_puerto(int fd){
	  int dato,unidad,decena,centena;
	  char rev[8];
	  read(fd, rev, 8);
      centena=(rev[0]-48)*100;
      decena=(rev[1]-48)*10;
      unidad=(rev[2]-48);
      dato=centena+decena+unidad;
      if (dato>500)dato=500;
      if(dato<0)dato=0;
      return dato;
}