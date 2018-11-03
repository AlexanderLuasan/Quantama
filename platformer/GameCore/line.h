#pragma once
#include "collisionObject.h"

class linecoll : public collisionobj
{
public:
	linecoll(int x1, int y1, int x2, int y2);
	bool Collision(collisionobj *other);
	poly getdraw();
private:
	int slopex;
	int slopey;
};
