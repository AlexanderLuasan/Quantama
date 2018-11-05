#include "player.h"

player::player()
{

}

player::player(int x, int y)
{
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

hitbox player::getcollision()
{
	return collision;
}

poly player::getdraw()
{
	return collision.getdraw();
}
