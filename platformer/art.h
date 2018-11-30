#pragma once
#include <allegro5/allegro.h>
#include "GameCore/rect.h"
class art
{
public:
	art();
	void delart();
	art(ALLEGRO_BITMAP*img,int x,int y,int w,int h);
	ALLEGRO_BITMAP * getimg();
	rectangle getbox();
private:
	ALLEGRO_BITMAP * image;
	rectangle box;


};