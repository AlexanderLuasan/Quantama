#include "poly.h"
#include <allegro5/allegro_primitives.h>



poly::poly(int x, int y)
{
	xpos = x;
	ypos = y;
	index = 0;
}

void poly::addpoint(int x, int y)
{
	xs[index] = x;
	ys[index] = y;
	index += 1;
}

int poly::getsize()
{
	return index;
}

int poly::xpoint(int index)
{
	return xs[index];
}

int poly::ypoint(int index)
{
	return ys[index];
}

int poly::getPosx()
{
	return xpos;
}

int poly::getPosy()
{
	return ypos;
}
