#pragma once
#include "collisionObject.h"

//note positive slop looks down
class triangle : public collisionobj
{
public:
	int id();
	triangle(int x1, int y1, int x2, int y2, int x3, int y3);
	poly getdraw();

	int leftR(collisionobj *other);
	int rightR(collisionobj *other);
	int bottomR(collisionobj *other);
	int topR(collisionobj *other);

private:
	bool slope;
	bool down;
};