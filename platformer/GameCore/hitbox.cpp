#include "hitbox.h"
#include <iostream>

hitbox::hitbox()
{
}

hitbox::hitbox(int x, int y, int width, int height)
{
	self = new rectangle(x, y, width, height);
}

hitbox::hitbox(int x1, int y1, int x2, int y2, int x3, int y3)
{
	self =  new triangle(x1, y1, x2, y2, x3, y3);
}

hitbox::hitbox(int x, int y, int radius)
{
	self =  new circle(x, y, radius);
}

hitbox::hitbox(int x1, int y1, int x2, int y2, bool line)
{
	self = new linecoll(x1, y1, x2, y2);
}

hitbox::hitbox(int x, int y)
{
	self = new point(x, y);
}



poly hitbox::getdraw()
{
	return self->getdraw();
}

poly hitbox::getcollision(hitbox other)
{
	return self->getcollision(other.self);
}

bool hitbox::collision(hitbox other)
{
	if (self->simplecolide(other.self)) {
		if (self->id() == 3) {
			if (self->Collision(other.self)){
				return true;
			}
		}
		else if (self->Collision(other.self)&&other.self->Collision(self)) {//change to type prioity
			return true;
		}


	}
	return false;
}

void hitbox::setx(int x)
{
	self->setX(x);
}

void hitbox::sety(int y)
{
	self->setY(y);
}

int hitbox::getx()
{
	return self->getX();
}

int hitbox::gety()
{
	return self->getY();
}

void hitbox::left(int v)
{
	self->left(v);
}

void hitbox::right(int v)
{
	self->right(v);
}

void hitbox::top(int v)
{
	self->top(v);
}

void hitbox::bottom(int v)
{
	self->bottom(v);
}

int hitbox::left(hitbox other)
{
	return self->leftR(other.self);
}

int hitbox::right(hitbox other)
{
	return self->rightR(other.self);
}

int hitbox::top(hitbox other)
{
	return self->topR(other.self);
}

int hitbox::bottom(hitbox other)
{
	return self->bottomR(other.self);
}

int hitbox::left()
{
	return this->self->left();
}

int hitbox::right()
{
	return this->self->right();
}

int hitbox::top()
{
	return self->top();
}

int hitbox::bottom()
{
	return this->self->bottom();
}

