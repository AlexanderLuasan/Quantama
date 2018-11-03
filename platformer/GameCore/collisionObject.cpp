#include "collisionObject.h"
#include <iostream>

using namespace std;
int collisionobj::id()
{
	return -1;
}

collisionobj::collisionobj()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

collisionobj::collisionobj(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	width = w;
	height = h;
}

poly collisionobj::getdraw()
{
	poly end = poly(0, 0);
	end.addpoint(0, 0);
	return end;
}

poly collisionobj::getcollision(collisionobj * other)
{
	poly end = poly(this->leftR(other), this->topR(other));
	end.addpoint(0,0);
	end.addpoint(this->rightR(other) - this->leftR(other),0);
	end.addpoint(this->rightR(other) - this->leftR(other), this->bottomR(other) - this->topR(other));
	end.addpoint(0, this->bottomR(other) - this->topR(other));
	return end;
}

bool collisionobj::simplecolide(collisionobj * other)
{
	if (this->top() < other->bottom() && this->bottom() > other->top()) {
		if (this->left() < other->right() && this->right() > other->left()){
			return true;
		}
	}
	return false;
}

bool collisionobj::Collision(collisionobj *other)
{
	if (horizonalCollision(other) && verticalCollision(other)) {
		return true;
	}
	else {
		return false;
	}
}

bool collisionobj::horizonalCollision(collisionobj *other)
{
	if (this->leftR(other) < other->rightR(this) && this->rightR(other) > other->leftR(this)) {
		return true;
	}
	return false;
}

bool collisionobj::verticalCollision(collisionobj *other)
{
	if (this->topR(other) < other->bottomR(this) && this->bottomR(other) > other->topR(this)) {
		return true;
	}
	return false;
}

int collisionobj::getH()
{
	return height;
}

int collisionobj::getW()
{
	return width;
}

int collisionobj::getX()
{
	return x;
}

int collisionobj::getY()
{
	return y;
}

void collisionobj::setH(int v)
{
	height = v;
}

void collisionobj::setW(int v)
{
	width = v;
}

void collisionobj::setX(int v)
{
	x = v;
}

void collisionobj::setY(int v)
{
	y = v;
}

int collisionobj::leftR(collisionobj *other)
{
	return this->left();
}

int collisionobj::rightR(collisionobj *other)
{
	return this->right();
}

int collisionobj::bottomR(collisionobj *other)
{
	return this->bottom();
}

int collisionobj::topR(collisionobj *other)
{
	return this->top();
}

void collisionobj::leftR(int v)
{
	this->left(v);
}

void collisionobj::rightR(int v)
{
	this->right(v);
}

void collisionobj::bottomR(int v)
{
	this->bottom(v);
}

void collisionobj::topR(int v)
{
	this->top(v);
}

int collisionobj::left()
{
	return this->getX();
}

int collisionobj::right()
{
	return this->getX()+this->getW();
}

int collisionobj::bottom()
{
	return this->getY()+this->getH();
}

int collisionobj::top()
{
	return this->getY();
}

void collisionobj::left(int v)
{
	this->setX(v);
}

void collisionobj::right(int v)
{
	this->setX(v - this->getW());
}

void collisionobj::bottom(int v)
{
	this->setY(v-this->getH());
}

void collisionobj::top(int v)
{
	this->setY(v);
}

void collisionobj::centerx(int v)
{
	this->setX(v - this->width / 2);
}

void collisionobj::centery(int v)
{
	this->setY(v - this->getH()/2);
}

int collisionobj::centerx()
{
	return this->getX()+this->getW()/2;
}

int collisionobj::centery()
{
	return this->getY()+this->getH()/2;
}
