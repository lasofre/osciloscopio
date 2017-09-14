#include <fcntl.h> 	
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <unistd.h> // close function
void dib(Display *d,Window w,int s);
int lectura_puerto(int fd);
void dib_signal(Display *d,Window w,int s,int k,int fd,XPoint puntos[500]);
int main( void ) {
  Display *d;
  Window w;
  XEvent e;
  int s,fd,chop=0;
  int dato=0,key; 
  int x=10,unidad,decena,centena;
  int y=0,i=0,j,k=1;
  XPoint puntos[500]={{10,10}};
  XColor xcolour;
  xcolour.red=0;xcolour.green=0;xcolour.blue=65535;
  xcolour.flags= DoRed | DoGreen | DoBlue;


   fd=iniciar_com("/dev/ttyACM0");//Inicio de comunicacion.

   d = XOpenDisplay(NULL);
   if (d == NULL) {
     fprintf(stderr, "No se pudo conectar al servidor gráfico\n");
     exit(1);
   }

   s = DefaultScreen(d);

                        /* crea la ventana */
    
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 700, 600, 1,0,BlackPixel(d,s));
  
   XSetStandardProperties(d,w,"Oscii","HI!",None,NULL,0,NULL);
   XSelectInput(d, w, ExposureMask | KeyPressMask);

                        /* muestra la ventana */
   XMapWindow(d, w);
   



   write(fd,"i",8);

  while(1){
    XNextEvent(d, &e);

    if (e.type == Expose) {
    
    XClearArea(d, w, 11, 11,509,409, 1);
      
      dato=lectura_puerto(fd);
      y=332-(dato/2);
      if(chop==1 && x<510){
      		if(x<=510){
      			x=x+k;
      			puntos[i].x=x;
      			puntos[i].y=y;
      			i++;
       		}
      		else{
        		x=10;
        		i=0;
      		}
      }
       
      if (chop==0){
       		if(x<=510){
      			x=x+k;
      			puntos[i].x=x;
      			puntos[i].y=y;
      			i++;
        	}
      		else{
        		x=10;
        		i=0;
      		}
      	}
      xcolour.red=0;xcolour.green=65535;xcolour.blue=0;
	  XAllocColor(d,DefaultColormap(d,s),&xcolour);
      XSetForeground(d, DefaultGC(d, s), xcolour.pixel);
      for(j=0;j<(i-1);j++)XDrawLine(d,w,DefaultGC(d,s),puntos[j].x,puntos[j].y,puntos[j+1].x,puntos[j+1].y); 
      dib(d,w,s); 
   

      
 	
    }
    if (e.type == KeyPress){
      key=e.xkey.keycode;
      
      switch(key){
        case 114:if(k<9)k++;break;
        case 113:if(k>1)k--;break;
        case 54:if(chop==0)chop=1;else chop=0;break;
        default:break;
      }

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
      XFlush(d);
}


