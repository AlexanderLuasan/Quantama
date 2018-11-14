#pragma once
#include "propertiesholder.h"
#include "GameCore/hitbox.h"
#include "art.h"

class zone
{
public:
	zone();
	zone(hitbox hit, propertyholder data);
	void addimage(art image);
	ALLEGRO_BITMAP * getImage();
	hitbox gethit();
	propertyholder getdata();
	poly getdraw();

private:
	art myimage;
	propertyholder mydata;
	hitbox collision;



};