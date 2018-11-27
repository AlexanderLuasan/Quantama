#include "art.h"

art::art()
{
	image = nullptr;
	box = rectangle(1, 1, 1, 1);
}

art::art(ALLEGRO_BITMAP * img,int x,int y,int w, int h)
{
	box = rectangle(x, y, w, h);
	image = img;
}

ALLEGRO_BITMAP * art::getimg()
{
	return image;
}

rectangle art::getbox()
{
	return box;
}
