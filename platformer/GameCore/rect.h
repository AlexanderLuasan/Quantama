#pragma once
#include "collisionObject.h"


class rectangle: public collisionobj
{
public:
	rectangle(int x,int y,int w,int h);
	int id();
	poly getdraw();

private:

};
