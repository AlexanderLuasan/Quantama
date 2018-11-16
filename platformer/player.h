#pragma once
#include "GameCore/hitbox.h"
#include "animationsheet.h"
#include <string>


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
	
	void animate();

	void setupimage();
	void setupimagebox();
	void setanimation(const char * name);

	ALLEGRO_BITMAP * getAnimationImage();
	hitbox getAnimationBox();

	void collisionWall(int left, int top, int right, int bottom);
	hitbox getcollision();
	poly getdraw();
private:

	int animationcounter;
	animationset myanimations;
	ALLEGRO_BITMAP * image;
	int up, left;
	hitbox imagebox;
	string animationstate;



	bool inair;
	int aim[2];//x then y;
	int vel[2] = { 0,0 };
	hitbox collision;


};
