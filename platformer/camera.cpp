#include "camera.h"

cammera::cammera(int x, int y, int range, double cone, double center, double size, double speed, bool back)
{
	this->x = x;
	this->y = y;
	this->range = range;
	angleconesize = cone;
	anglecenter = center;
	anglerotationsize = size;
	this->speed = speed;
	currentangle = anglecenter;
	direction = 1;
	backrow = back;
}

void cammera::move()
{
	currentangle += speed * direction;
	if (currentangle > anglecenter + angleconesize) {
		direction = -1;
	}
	else if (currentangle < anglecenter - angleconesize) {
		direction = 1;
	}
}

double cammera::getangle()
{
	return currentangle;
}

double cammera::getanglesize()
{
	return angleconesize;
}

int cammera::getrange()
{
	return range;
}

int cammera::getx()
{
	return x;
}

int cammera::gety()
{
	return y;
}

hitbox cammera::getcolision()
{
	int x1, x2, y1, y2;
	x1 = x;
	y1 = y;
	x2 = x + cos(currentangle)*range;
	y2 = y + sin(currentangle)*range;
	return hitbox(x,y,x2,y2,0);
}

bool cammera::background()
{
	return backrow;
}
