/*
 * 	Functions:
 * --displaySetUp(Xsize,YSize)
 * --UpdateDisplay();
*/

/*	Include X Library Headers	*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/*	Include Starndar Lib Headers	*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*	Global Variables	*/
Display	*dis;
Window 	win;
GC 	gc;
XEvent 	event;
KeySym 	key;

int	screen;
int 	screenHeight = 500;
int 	screenWidth = 500;
float	axisRotation = 0;

unsigned long chartreuse; 


/*	Declare X Routines	*/
void init_x();
void close_x();
void redraw();

/*	Startup Functions	*/




void displayUpdate()	{
	XNextEvent(dis, &event);
}

/*	Update/Decloration Functions	*/
void init_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		screenWidth, screenHeight, 5,black, white);//Window Size
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
void displaySetUp(int width, int height)	{
	screenHeight	= height;
	screenWidth	= width;
	init_x();
}
void setColour(long n)	{
	chartreuse = n;
	XSetForeground(dis,gc,chartreuse);
}
/*	Used for Setting ForeGround Colour	*/

void get_colors() {
	XColor tmp;
	XParseColor(dis, DefaultColormap(dis,screen), "chartreuse", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	chartreuse=tmp.pixel;
};

/*
 ********************************
 *	Drawing Functions	*
 ********************************
*/
void rect(float x1, float y1, float width, float height)	{
	XFillRectangle(dis, win, gc, x1+(screenWidth/2), (((y1*-1)+screenHeight/2))-height, width, height);
}
void line(float x1, float y1, float x2, float y2)	{
	XDrawLine(dis, win, gc, x1+(screenWidth/2),(y1*-1)+(screenHeight/2), x2+(screenWidth/2),(y2*-1)+(screenHeight/2));	
}
void rotate()	{
	axisRotation += 0.1;
}
void twoDAxis()	{
	float axisYPos =	screenHeight/2 * (sin(axisRotation)); 
	float axisXPos =	screenHeight/2 * (cos(axisRotation)); 
	line(-1*axisXPos,axisYPos,axisXPos,-1*(axisYPos));
	line(screenWidth/2,0,-1*(screenWidth/2),0);
}
