#pragma once
#include "rect.h"
#include "circle.h"
#include "triangle.h"
#include "line.h"
#include "point.h"

class hitbox
{
public:
	hitbox(int x,int y,int width,int height);
	hitbox(int x1, int y1, int x2, int y2, int x3, int y3);
	hitbox(int x, int y, int radius);
	hitbox(int x1, int y1, int x2, int y2, bool line);
	hitbox(int x, int y);

	poly getdraw();
	poly getcollision(hitbox other);

	bool collision(hitbox other);

	//moving

	void setx(int x);
	void sety(int y);
	int getx();
	int gety();

	void left(int v);
	void right(int v);
	void top(int v);
	void bottom(int v);

	int left(hitbox other);
	int right(hitbox other);
	int top(hitbox other);
	int bottom(hitbox other);

private:
	collisionobj * self;

};




