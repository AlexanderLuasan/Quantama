#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GameCore/poly.h"
#define globaladjust 10
#define globalscale 2
class display
{
public:
	display(int width, int height, int scale);
	ALLEGRO_DISPLAY * gets();

	bool setCam(int x, int y);
	bool adjCam(int x, int y);
	bool drawstart();
	bool drawview();
	bool draw(ALLEGRO_BITMAP*image,int x,int y,int w,int h);
	bool draw(poly shape);
	bool draw(int x, int y, int w, int h);
private:
	int scale;
	int camx;
	int camy;
	int width;//screen
	int height;//screen

	ALLEGRO_DISPLAY * screen;
};