/* 
	Remember to compile try:
		1) gcc hi.c -o hi -lX11
		2) gcc hi.c -I /usr/include/X11 -L /usr/X11/lib -lX11
		3) gcc hi.c -I /where/ever -L /who/knows/where -l X11

	Brian Hammond 2/9/96.    Feel free to do with this as you will!
*/


/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/* include some silly stuff */
#include <stdio.h>
#include <stdlib.h>

/* here are our X variables */
Display *dis; //Display points to the X server
int screen; //Refers to which screen of the display to use
Window win; //Controls the Actualy window
GC gc; //Graphic context

int height = 500;
int width = 500;

unsigned long chartreuse;

/* here are our X routines declared! */
void init_x();
void close_x();
void redraw();

void get_colors() {
	XColor tmp;

	XParseColor(dis, DefaultColormap(dis,screen), "chartreuse", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	//chartreuse=tmp.pixel;
};

main () {
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	init_x();
	//get_colors();
	//XSetForeground(dis,gc,"RGBi:1.0/0.0/0.0");

	/* look for events forever... */
	while(1) {	
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		//hedraw();

		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			redraw();
		}
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				close_x();
			}
			printf("You pressed the %c key!\n",text[0]);
		}
		if (event.type==ButtonPress) {
		/* tell where the mouse Button was Pressed */
			int x=event.xbutton.x,
			    y=event.xbutton.y;

			strcpy(text,"X is FUN!");
			XSetForeground(dis,gc,rand()%event.xbutton.x%255);
			XDrawString(dis,win,gc,x,y, text, strlen(text));
		}
	}
}

void line(float x1, float y1, float x2, float y2)	{
	XDrawLine(dis, win, gc, x1+250,(y1*-1)+250, x2+250,(y2*-1)+250);	
}


void hedraw()	{
	line(0,250,0,-250);
	line(250,0,-250,0);
	float inc = 0.1;
	for (float i = -50; i < 50-inc; i+=inc)	{
		line(i,i*i,i+inc,(i+inc)*(i+inc));
	}
};

void init_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		width, height, 5,black, white);//Window Size
	XSetStandardProperties(dis,win,"Howdy","Hi",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

void redraw() {
	XClearWindow(dis, win);
};
