#include "art.h"

art::art()
{
	image = nullptr;
}

art::art(ALLEGRO_BITMAP * img)
{
	image = img;
}

ALLEGRO_BITMAP * art::getimg()
{
	return image;
}
