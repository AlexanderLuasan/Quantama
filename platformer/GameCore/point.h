#pragma once
#include "collisionObject.h"
class point : public collisionobj
{
public:
	point(int x, int y);
	poly getdraw();
};