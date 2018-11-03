#pragma once
#include <allegro5/allegro.h>


class plate
{
public:
	plate();
	plate(int width, int height);

	void addtile(ALLEGRO_BITMAP * tile, int x, int y, int width, int height);
	int getheight();
	int getwidth();
	ALLEGRO_BITMAP * draw();
private:
	ALLEGRO_BITMAP * map;
	int width, height;

};