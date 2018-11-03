#include "circle.h"

circle::circle(int x, int y, int radius)
{
	this->setW(radius * 2);
	this->setH(radius * 2);
	this->centerx(x);
	this->centery(y);

}

int circle::id()
{
	return 1;
}

poly circle::getdraw()
{
	poly end = poly(this->getX(),this->getY());
	int radius = this->getW()/2;
	//eight point plan
	//-90 -45 0 45 90
	end.addpoint(0,radius);
	end.addpoint(radius * (1.0-s45), radius * (1.0 - s45));
	end.addpoint(radius, 0);
	end.addpoint(radius+radius * s45, radius * (1.0 - s45));
	end.addpoint(2*radius,radius);
	end.addpoint(radius + radius * s45, radius + radius * s45);
	end.addpoint(radius, radius*2);
	end.addpoint(radius * (1.0 - s45),radius+ radius * s45);

	return end;
}

int circle::leftR(collisionobj * other)
{
	int pos;
	if (other->bottom() < this->centery()) {
		pos = this->centery() - other->bottom();
	}
	else if (other->top()>this->centery()) {
		pos = other->top() - this->centery();
	}
	else {
		return(this->left());
	}

	return this->centerx()-(sqrt(((this->getW() / 2)*(this->getW() / 2)) - (pos*pos)));
}
int circle::rightR(collisionobj * other)
{
	int pos;
	
	
	if (other->top()>this->centery()) {
		pos = other->top() - this->centery();
	}
	else if (other->bottom() < this->centery()) {
		pos = this->centery() - other->bottom();
	}
	else {
		return(this->right());
	}

	return this->centerx() + (sqrt(((this->getW() / 2)*(this->getW() / 2)) - (pos*pos)));
}

int circle::bottomR(collisionobj * other)
{
	int pos;


	if (other->left()>this->centerx()) {
		pos = other->left() - this->centerx();
	}
	else if (other->right() < this->centerx()) {
		pos = this->centerx() - other->right();
	}
	else {
		return(this->bottom());
	}

	return this->centery() + (sqrt(((this->getH() / 2)*(this->getH() / 2)) - (pos*pos)));
}

int circle::topR(collisionobj * other)
{
	int pos;


	if (other->left()>this->centerx()) {
		pos = other->left() - this->centerx();
	}
	else if (other->right() < this->centerx()) {
		pos = this->centerx() - other->right();
	}
	else {
		return(this->top());
	}

	return this->centery() - (sqrt(((this->getW() / 2)*(this->getW() / 2)) - (pos*pos)));
}


