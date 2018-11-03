#pragma once
#include <cmath>
#include "collisionObject.h"
#define s45 0.707106
//s45 0.707106

class circle : public collisionobj
{
public:
	circle(int x, int y, int radius);
	int id();
	poly getdraw();
	int leftR(collisionobj *other);
	int rightR(collisionobj *other);
	int bottomR(collisionobj *other);
	int topR(collisionobj *other);
private:

};