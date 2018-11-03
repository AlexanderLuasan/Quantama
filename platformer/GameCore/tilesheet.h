#pragma once
#include <allegro5/allegro.h>
class sheet
{
public:
	sheet();
	sheet(const char *name,int size,int tilew,int tileh,int countw,int counth);
	ALLEGRO_BITMAP * getar(int i);
	ALLEGRO_BITMAP * getar(int x, int y);
	int getcount();
	int getw();
	int geth();
private:
	ALLEGRO_BITMAP * mainsheet;
	int width;
	int height;

	int verticalcount;
	int horizonalcount;
};