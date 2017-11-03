//asdf
#include <fcntl.h> 	
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <unistd.h> // close function
#include <time.h>
#include <sys/time.h>

void parametros(Display *d,Window w,int s,char *smin ,char *smax,char *sfrec,char *sk);
void longitud (Display *d,Window w,int s,int k,char *k1);
void dib( Display *d,Window w,int s);
int lectura_puerto(int fd);
void dib_signal(Display *d,Window w,int s,int k,int fd,XPoint puntos[500]);
double tiempo(int fd,int min, int max);
void picos(int fd,int *max,int *min);
int muestras(int k ,XPoint *puntos,int fd);
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}


int main( void ) {
  Display *d;
  Window w;
  XEvent e;
  int s,fd,chop=0,max=0,min=0,salida=1;
  int dato=0,key; 
  int y=0,i=0,j,k=1,c=0,z=0;
  double frec=0;
  char *smax,*smin,*sfrec,*sk;
  float aux;

   sfrec=malloc(4* sizeof(char));
   smin=malloc(4* sizeof(char));
   smax=malloc(4* sizeof(char));
   sk=malloc(4* sizeof(char));

  XPoint puntos[500]={{10,10}};
  XPoint *puntos;
  XColor xcolour;
  xcolour.red=0;xcolour.green=0;xcolour.blue=65535;
  xcolour.flags= DoRed | DoGreen | DoBlue;
  puntos=malloc(500* sizeof(XPoint));

   fd=iniciar_com("/dev/ttyACM0");//Inicio de comunicacion.

   d = XOpenDisplay(NULL);
   if (d == NULL) {
     fprintf(stderr, "No se pudo conectar al servidor gráfico\n");
     exit(1);
   }

   s = DefaultScreen(d);

                        /* crea la ventana */
    
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 730, 600, 1,0,BlackPixel(d,s));
  
   XSetStandardProperties(d,w,"Oscii","HI!",None,NULL,0,NULL);
   XSelectInput(d, w, ExposureMask | KeyPressMask);

                        /* muestra la ventana */
   XMapWindow(d, w);
   

	
   write(fd,"i",8);
	

   picos(fd,&max,&min);	
   frec=tiempo(fd,min,max);
   aux=max;
   aux=aux/100;
    
   sprintf(smax,"%.2f", aux);
   
    aux=frec;
   sprintf(sfrec,"%.2f",aux);
   printf("%s\n",sfrec);
   sprintf(sk,"%d",k);

  while(salida==1){
    XNextEvent(d, &e);

    if (e.type == Expose) {

			//parametros(d,w,s,smin,smax,sfrec,sk);
			dib(d,w,s);

			xcolour.red=0;xcolour.green=65535;xcolour.blue=0;
			XAllocColor(d,DefaultColormap(d,s),&xcolour);
		    XSetForeground(d, DefaultGC(d, s), xcolour.pixel);
		 	for(j=0;j<(i-1);j++)XDrawLine(d,w,DefaultGC(d,s),puntos[j].x,puntos[j].y,puntos[j+1].x,puntos[j+1].y);
		           
    }
    if (e.type == KeyPress){
      key=e.xkey.keycode;
      
      switch(key){
        case 114:	
        			if(k<9){ k++;
					    longitud(d,w,s,k,sk);
						}break;
        case 113:
        			if(k>1){k--;
			          longitud(d,w,s,k,sk);
			          }break;
        case 54:
				if(chop==0)chop=1;else chop=0;break;

	    case 39:
				salida=0;break;

		case 34:
		        


		
		default:break;
			      }
		
     	}
     
	      if(chop==0){
					XClearArea(d, w, 11, 11,509,409, 1);
					i=muestras(k,puntos,fd);
	  		    	for(j=0;j<(i-1);j++)XDrawLine(d,w,DefaultGC(d,s),puntos[j].x,puntos[j].y,puntos[j+1].x,puntos[j+1].y);
					XFlush(d);
	      	}

   		 

  }
 
    /* close connection to server */
   XCloseDisplay(d);

  close(fd);
  return 0;
  
}


void dib( Display *d,Window w,int s){



      XColor xcolour;
      xcolour.red=0;xcolour.green=0;xcolour.blue=65535;
      xcolour.flags= DoRed | DoGreen | DoBlue;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s),xcolour.pixel );
      XDrawRectangle(d, w, DefaultGC(d, s), 10, 10,510, 410);

      xcolour.red=0;xcolour.green=0;xcolour.blue=65535;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s), xcolour.pixel);
      XDrawLine(d,w,DefaultGC(d, s), 10,215, 520,215);
      XDrawLine(d,w,DefaultGC(d, s), 265,10, 265,420); 
      XDrawRectangle(d, w, DefaultGC(d, s), 10, 430,510, 160); 
      XDrawRectangle(d, w, DefaultGC(d, s), 614, 436,20, 20);
      XDrawRectangle(d, w, DefaultGC(d, s), 545, 436,20, 20); 
      XDrawRectangle(d, w, DefaultGC(d, s), 582, 485,20, 20);
      XDrawRectangle(d, w, DefaultGC(d, s), 582, 525,20, 20);    
      XDrawRectangle(d, w, DefaultGC(d, s), 582, 565,20, 20);

      xcolour.red=0;xcolour.green=0;xcolour.blue=15000;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s), xcolour.pixel);
      
      XDrawLine(d,w,DefaultGC(d, s), 10,265, 520,265);
      XDrawLine(d,w,DefaultGC(d, s), 10,315, 520,315); 
      XDrawLine(d,w,DefaultGC(d, s), 10,365, 520,365); 
      XDrawLine(d,w,DefaultGC(d, s), 10,165, 520,165); 
      XDrawLine(d,w,DefaultGC(d, s), 10,115, 520,115);
      XDrawLine(d,w,DefaultGC(d, s), 10,65, 520,65); 
      

      XDrawLine(d,w,DefaultGC(d, s), 315,10, 315,420);
      XDrawLine(d,w,DefaultGC(d, s), 365,10, 365,420);
      XDrawLine(d,w,DefaultGC(d, s), 415,10, 415,420);
      XDrawLine(d,w,DefaultGC(d, s), 465,10, 465,420);
      XDrawLine(d,w,DefaultGC(d, s), 215,10, 215,420); 
      XDrawLine(d,w,DefaultGC(d, s), 165,10, 165,420);
      XDrawLine(d,w,DefaultGC(d, s), 115,10, 115,420);
      XDrawLine(d,w,DefaultGC(d, s), 65,10, 65,420);  

      xcolour.red=0;xcolour.green=65535;xcolour.blue=0;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s), xcolour.pixel);

      XDrawString(d,w,DefaultGC(d, s),15,450, "OSCILOSCOPIO DIGITAL" , 20);
      
      XDrawString(d,w,DefaultGC(d, s),15,580, "BUCCA MATIAS, RODRIGUEZ IGNACIO" , 31);

      XDrawString(d,w,DefaultGC(d, s),405,580, "CREACION: 1/11/2017" , 19);

      XDrawString(d,w,DefaultGC(d, s),460,450, "V1.0 BETA" , 9);

      XDrawString(d,w,DefaultGC(d, s),550,450, "<-" , 2);
      XDrawString(d,w,DefaultGC(d, s),620,450, "->" , 2);

      XDrawString(d,w,DefaultGC(d, s),650,450, "VAR.LONG" , 8);

      XDrawString(d,w,DefaultGC(d, s),590,500, "C" , 1);
      XDrawString(d,w,DefaultGC(d, s),630,500, "CHOP" , 4);

      XDrawString(d,w,DefaultGC(d, s),590,540, "P" , 1);
      XDrawString(d,w,DefaultGC(d, s),630,540, "PARAMETROS" , 10);

      XDrawString(d,w,DefaultGC(d, s),590,580, "S" , 1);
      XDrawString(d,w,DefaultGC(d, s),630,580, "SALIR" , 5);

      XDrawString(d,w,DefaultGC(d, s),225,515, "PROYECTO OSCII" , 14);
      


      XFlush(d);

      
}

double tiempo(int fd,int min , int max)
{
  struct timeval t_ini, t_fin;
  double secs=0;
  float frec=0;
  int flag=0,y;
  gettimeofday(&t_ini, NULL);
  while(flag<3){
      y=lectura_puerto(fd);
      if(y>(max-20) && flag==0)flag++;
      if(y<(min+20)&& flag==1) flag++;
      if(y>(max-20) && flag==2)flag++;
  }
  gettimeofday(&t_fin, NULL);

  secs = timeval_diff(&t_fin, &t_ini);
  //printf("%.16g milliseconds\n", secs * 1000.0);
  frec = 1/(secs);
  //printf("%.16g hz\n", frec);
  return frec;
}

void longitud (Display *d,Window w,int s,int k,char *k1){

    XClearArea(d, w, 610,315,15,15, 1);
    sprintf(k1,"%d", k);
      
    XColor xcolour;
    xcolour.red=0;xcolour.green=65535;xcolour.blue=0;
    xcolour.flags= DoRed | DoGreen | DoBlue;
    XAllocColor(d,DefaultColormap(d,s),&xcolour);
    XSetForeground(d, DefaultGC(d, s),xcolour.pixel );
    XDrawString(d,w,DefaultGC(d, s),610,325, k1 , 1);

}
void parametros(Display *d,Window w,int s,char *smin ,char *smax,char *sfrec,char *sk){
 	  XColor xcolour;

	  xcolour.red=0;xcolour.green=0;xcolour.blue=65535;
      xcolour.flags= DoRed | DoGreen | DoBlue;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s),xcolour.pixel );
      XDrawRectangle(d, w, DefaultGC(d, s), 525, 10,200, 410);

      
      xcolour.red=0;xcolour.green=65535;xcolour.blue=0;
      XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s), xcolour.pixel);

     XDrawString(d,w,DefaultGC(d, s),530,45, "FRECUENCIA APROXIMADA:" , 22);
      XDrawString(d,w,DefaultGC(d, s),580,85, sfrec ,4);
      XDrawString(d,w,DefaultGC(d, s),640,85, "Hz" , 2);

      
      XDrawString(d,w,DefaultGC(d, s),530,165, "TENSION PICO APROXIMADA:" , 24);
      XDrawString(d,w,DefaultGC(d, s),580,205, smax, 4);
      XDrawString(d,w,DefaultGC(d, s),630,205, "V" , 1);


      XDrawString(d,w,DefaultGC(d, s),530,285, "VARIACION DE LONG. DE ONDA:" , 27);
      XDrawString(d,w,DefaultGC(d, s),610,325, sk , 1);

    //XFlush(d);
}
void picos(int fd,int *max,int *min){
	int i =0,dato=0;
	dato=lectura_puerto(fd);
	*max=dato;
	*min=dato;
	for(i=0;i<500;i++){
	dato=lectura_puerto(fd);
	if(dato>*max)*max=dato;
	if(dato<*min)*min=dato;
}
}
int muestras(int k ,XPoint *puntos,int fd){
	int i=0,x=10,y,dato;		
	while(x<510){	
			dato=lectura_puerto(fd);
               		y=332-(dato/2);
      			puntos[i].x=x;
      			puntos[i].y=y;
			x=x+k;
			i++;
       		}
	return (i-1);	
}
