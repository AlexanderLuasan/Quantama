#pragma once
#include "GameCore/hitbox.h"
class player
{
public:
	player();
	player(int x,int y);

	bool setpos(int x, int y);
	bool adjpos(int x, int y);


	hitbox getcollision();
	poly getdraw();
private:
	
	hitbox collision;


};
