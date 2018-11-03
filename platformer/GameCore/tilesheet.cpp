#include "tilesheet.h"
#include <iostream>
sheet::sheet()
{

}

sheet::sheet(const char *path, int size, int tilew, int tileh, int countw, int counth)
{
	std::cout << "path: " << path;
	mainsheet = al_load_bitmap(path);
	width = tilew;
	height = tileh;
	verticalcount = counth;
	horizonalcount = countw;

}

ALLEGRO_BITMAP * sheet::getar(int i)
{
	int x = i % horizonalcount;
	int y = i / horizonalcount;
	return this->getar(x, y);
}

ALLEGRO_BITMAP * sheet::getar(int x, int y)
{
	ALLEGRO_BITMAP *end = al_create_sub_bitmap(mainsheet, x*width, y*height, width, height);
	return end;

}

int sheet::getcount()
{
	return verticalcount*horizonalcount;
}

int sheet::getw()
{
	return width;
}

int sheet::geth()
{
	return height;
}
