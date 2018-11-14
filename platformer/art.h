#pragma once
#include <allegro5/allegro.h>
class art
{
public:
	art();
	art(ALLEGRO_BITMAP*img);
	ALLEGRO_BITMAP * getimg();
private:
	ALLEGRO_BITMAP * image;



};