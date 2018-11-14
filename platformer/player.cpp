#include "player.h"
#include <iostream>
player::player()
{

}

player::player(int x, int y)
{
	inair = true;
	collision = hitbox(0, 0, 16, 16);
	collision.setx(x - 8);
	collision.sety(y - 16);

}

bool player::setpos(int x, int y)
{
	collision.setx(x - 8);
	collision.sety(y - 16);
	return false;
}

bool player::adjpos(int x, int y)
{
	collision.setx(x + collision.getx());
	collision.sety(y + collision.gety());
	return false;
}

bool player::setxaim(int dir)
{
	if (dir > 0) {
		aim[0] = 1;
	}
	else if (dir < 0) {
		aim[0] = -1;
	}
	else {
		aim[0] = 0;
	}
	return false;
}

bool player::setyaim(int dir)
{
	if (dir < 0) {
		aim[1] = -1;
	}
	else if (dir > 0) {
		aim[1] = 1;
	}
	else {
		aim[1] = 0;
	}
	return false;
}

bool player::setjump(bool jumping)
{
	if (inair) {
		return false;
	}
	else if(!inair && jumping){
		inair = true;
		vel[1] = -60;
	}
}

void player::positionupdate()
{
	if (aim[0] > 0 && vel[0] < 100) {
		if (vel[0] == 0) {
			vel[0] = 10;
		}
		else {
			vel[0] += 1;
		}
		
	}
	else if (aim[0] < 0 && vel[0] > -100) {
		if (vel[0] == 0) {
			vel[0] = -10;
		}
		else {
			vel[0] -= 1;
		}
	}
	else if (aim[0]==0) {
		if (vel[0] < 0) {
			vel[0] += 2;
		}
		else if(vel[0] > 0){
			vel[0] -= 2;
		}

		if (vel[0] == 1 || vel[0] == -1) {
			vel[0] = 0;
		}
	}
	else if(aim[0]<0 && vel[0]>0) {
		vel[0] -= 4;
	}
	else if (aim[0]>0 && vel[0]<0) {
		vel[0] += 4;
	}

	if (vel[1] < 100) {
		vel[1] += 3;
	}

	this->adjpos(vel[0]*xmaxspeed/100,vel[1]*terminalvel/100);


}

void player::collisionWall(int left, int top, int right, int bottom)
{
	//options shortest change

	int distances[4];//left top right bottom

	distances[0] = abs(left - this->collision.right());
	distances[1] = abs(top - this->collision.bottom());
	distances[2] = abs(right - this->collision.left());
	distances[3] = abs(bottom - this->collision.top());

	int min = 0;
	for (int i = 0; i < 4; i++) {
		if (distances[i] < distances[min]) {
			min = i;
		}
	}
	//std::cout << "min"<< min << std::endl;
	switch (min)
	{
	case 0:
		collision.right(left);
		vel[0] = 0;
		break;
	case 1:
		collision.bottom(top);
		inair = false;
		break;
	case 2:
		collision.left(right);
		vel[0] = 0;
		break;
	case 3:
		collision.top(bottom);
		vel[1] = 0;
		break;
	default:
		break;
	}

}

hitbox player::getcollision()
{
	return collision;
}

poly player::getdraw()
{
	return collision.getdraw();
}
