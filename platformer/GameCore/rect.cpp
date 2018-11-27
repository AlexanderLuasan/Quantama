#include "rect.h"

using namespace std;


rectangle::rectangle()
{
	this->setX(1);
	this->setY(1);
	this->setW(1);
	this->setH(1);
}

rectangle::rectangle(int x, int y, int w, int h)
{
	this->setX(x);
	this->setY(y);
	this->setW(w);
	this->setH(h);
}

int rectangle::id()
{
	return 0;
}

poly rectangle::getdraw()
{

	poly end = poly(this->getX(),this->getY());
	end.addpoint(0, 0);
	end.addpoint(this->getW(), 0);
	end.addpoint(this->getW(), this->getH());
	end.addpoint(0, this->getH());

	return end;
}



