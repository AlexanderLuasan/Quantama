#pragma once
#include "GameCore/hitbox.h"

#define xmaxspeed 10  // 10 pix per sec 
#define terminalvel 10 

class player
{
public:
	player();
	player(int x,int y);

	bool setpos(int x, int y);
	bool adjpos(int x, int y);

	bool setxaim(int dir);
	bool setyaim(int dir);

	bool setjump(bool jumping);

	void positionupdate();
	
	void collisionWall(int left, int top, int right, int bottom);
	hitbox getcollision();
	poly getdraw();
private:
	bool inair;
	int aim[2];//x then y;
	int vel[2] = { 0,0 };
	hitbox collision;


};
