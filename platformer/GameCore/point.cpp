#include "point.h"

point::point(int x, int y)
{
	this->setX(x);
	this->setY(y);
	this->setW(1);
	this->setH(1);
}

poly point::getdraw()
{
	poly end = poly(this->getX(), this->getY());
	end.addpoint(0, 0);
	end.addpoint(this->getW(), 0);
	end.addpoint(this->getW(), this->getH());
	end.addpoint(0, this->getH());

	return end;
}
