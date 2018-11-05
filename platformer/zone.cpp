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
