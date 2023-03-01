#include <stdio.h>
#include <math.h>
#include "window.h"

int height = 500;
int width  = 500;

/*
void drawScalarField(float sampleNumber)	{
	//Equaiton for now
	for (int y = -height/2; y < height/2; y+=height/sampleNumber)	{
		for (int x = -width/2; x < width/2; x+=width/sampleNumber)	{
			float z = (sin(x/50)+sin(y/50))+2;
			//setColour(-1*(x+(width/2)));
			char colour[25];	
			float R = 1.0;
			float G = 0.0;
			float B = 0.0;
			//sprintf(colour,"RGBi:%f/%f/%f",R,G,B);
			//setColour(colour);
			//rect(x,y,width/sampleNumber, height/sampleNumber);
		}
	}
	setColour(0);	
	twoDAxis();
}
*/

void drawVector(float xloc, float yloc, float vecX, float vecY, int mag)	{
	float normalMag = sqrt((vecX*vecX)+(vecY*vecY));
	if (normalMag > 1)	{
		line(xloc, yloc, xloc+(vecX*mag/normalMag), yloc+(vecY*mag/normalMag));
	}
}

void vectorField(float sampleNumber, int magnitude)	{
	for (float y = -height/2; y < height/2; y+=height/sampleNumber)	{
		for (float x = -width/2; x < width/2; x+=width/sampleNumber)	{
			float dirX = ((y+100)-(x+100));
			float dirY = (-(y+100)-(x+100));
			drawVector(x, y, dirX, dirY, -magnitude);
			//drawVector(x, y,-1*dirY/2,dirX/2,magnitude/5);
			//drawVector(x, y,dirY/2,-1*dirX/2,magnitude/5);
			//Possible Better Vector Direction Representation
		}
	}
}


void main()	{
	displaySetUp(500,500);	
	line(0.0,0.0,500.0,500.0);
	int i = 0;
	while(1)	{
		scanf("%d",&i);
		if(i == 1)	{
			rotate();
			redraw();
			i = 0;
		}
		displayUpdate();	//This is needed so the window doesn't get over run
		line(-50,50,50,50);
		twoDAxis();
		//drawScalarField(500);
		//drawVector(0.0,0.0,1.0,1.0,5);
		vectorField(50, 10);
	}
}

