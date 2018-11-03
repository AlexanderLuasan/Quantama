#pragma once
#include "poly.h"


class collisionobj
{
public:


	virtual int id();
	collisionobj();
	collisionobj(int x,int y,int w,int h);
	virtual poly getdraw();
	poly getcollision(collisionobj *other);

	bool simplecolide(collisionobj *other);
	virtual bool Collision(collisionobj *other);
	bool horizonalCollision(collisionobj *other);
	bool verticalCollision(collisionobj *other);

	int getH();
	int getW();
	int getX();
	int getY();
	void setH(int v);
	void setW(int v);
	void setX(int v);
	void setY(int v);


	//relative
	virtual int leftR(collisionobj *other);
	virtual int rightR(collisionobj *other);
	virtual int bottomR(collisionobj *other);
	virtual int topR(collisionobj *other);
	void leftR(int v);
	void rightR(int v);
	void bottomR(int v);
	void topR(int v);



	int left();
	int right();
	int bottom();
	int top();
	void left(int v);
	void right(int v);
	void bottom(int v);
	void top(int v);
	
	void centerx(int v);
	void centery(int v);
	int centerx();
	int centery();

private:
	int x, y, width, height;

};

