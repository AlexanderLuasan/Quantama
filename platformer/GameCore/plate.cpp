#include "plate.h"

plate::plate()
{
	map = al_create_bitmap(1, 1);
	width = -1;
	height=-1;

}

plate::plate(int w, int h)
{
	width = w;
	height = h;
	map = al_create_bitmap(width, height);

}

void plate::addtile(ALLEGRO_BITMAP * tile, int x, int y, int width, int height)
{
	al_set_target_bitmap(map);
	al_draw_bitmap_region(tile, 0, 0, width, height, x, y,0);

}

int plate::getheight()
{
	return height;
}

int plate::getwidth()
{
	return width;
}

ALLEGRO_BITMAP * plate::draw()
{
	return map;
}
