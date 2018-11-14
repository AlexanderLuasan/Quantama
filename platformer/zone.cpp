#include "zone.h"

zone::zone()
{
	collision = hitbox(0, 0, 0, 0);
}

zone::zone(hitbox hit, propertyholder data)
{
	collision = hit;
	mydata = data;
}

void zone::addimage(art image)
{
	myimage = image;
}

ALLEGRO_BITMAP * zone::getImage()
{
	return myimage.getimg();
}

hitbox zone::gethit()
{
	return collision;
}

propertyholder zone::getdata()
{
	return mydata;
}

poly zone::getdraw()
{
	return collision.getdraw();
}
