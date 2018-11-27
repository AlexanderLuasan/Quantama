#pragma once
#include "GameCore/hitbox.h"
#include <cmath>
#include <iostream>
class cammera
{
public:
	cammera(int x, int y, int range, double cone, double center, double size,double speed);
	void move();
	double getangle();
	double getanglesize();
	int getrange();
	int getx();
	int gety();
	hitbox getcolision();
private:
	int x, y;
	int range;
	double angleconesize;
	double anglecenter;
	double anglerotationsize;
	double speed;

	

	double currentangle=0;
	int direction = 0;

};

