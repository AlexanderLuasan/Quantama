#include "player.h"
#include <iostream>
player::player()
{
	myanimations = animationset("player.tmx");
}

player::player(int x, int y)
{
	myanimations = animationset("player.tmx");
	inair = true;
	collision = hitbox(0, 0, 16, 16);
	collision.setx(x - 8);
	collision.sety(y - 16);
	animationstate = "idle";
	this->setanimation("idle");
	this->setupimage();
	animationcounter = 0;
	animationloopcounter = 0;
	duck = false;
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
		duck = false;
	}
	else if (dir > 0) {
		aim[1] = 1;
		duck = true;
	}
	else {
		aim[1] = 0;
		duck = false;
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
	if (aim[0] != 0) {
		if (inair) {
			if (aim[0] > 0 && vel[0] < 25) {
				if (vel[0] == 0) {
					vel[0] = 10;
				}
				else {
					vel[0] += 1;
				}

			}
			else if (aim[0] < 0 && vel[0] > -25) {
				if (vel[0] == 0) {
					vel[0] = -10;
				}
				else {
					vel[0] -= 1;
				}
			}
		}
		else if (duck) {
			if (abs(vel[0]) > 50) {
				if (vel[0] > 1) {
					vel[0] = 50;
				}
				else {
					vel[0] = -50;
				}
			}
			if (aim[0] > 0 && vel[0] < 50) {
				if (vel[0] == 0) {
					vel[0] = 25;
				}
				else {
					vel[0] += 1;
				}

			}
			else if (aim[0] < 0 && vel[0] > -50) {
				if (vel[0] == 0) {
					vel[0] = -25;
				}
				else {
					vel[0] -= 1;
				}
			}
		}
		else {
			if (aim[0] > 0 && vel[0] < 100) {
				if (vel[0] == 0) {
					vel[0] = 25;
				}
				else {
					vel[0] += 1;
				}

			}
			else if (aim[0] < 0 && vel[0] > -100) {
				if (vel[0] == 0) {
					vel[0] = -25;
				}
				else {
					vel[0] -= 1;
				}
			}
		}
	}
	else if (aim[0]==0) {
		if (inair||duck) {
			if (vel[0] < 0) {
				vel[0] += 1;
			}
			else if (vel[0] > 0) {
				vel[0] -= 1;
			}

			if (vel[0] == 1 || vel[0] == -1) {
				vel[0] = 0;
			}
		}
		else {
			if (vel[0] < 0) {
				vel[0] += 2;
			}
			else if (vel[0] > 0) {
				vel[0] -= 2;
			}

			if (vel[0] == 1 || vel[0] == -1) {
				vel[0] = 0;
			}
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

	if (vel[0] < 0) {
		fliped = true;
	}
	else if(vel[0] > 0){
		fliped = false;
	}
	this->adjpos(vel[0]*xmaxspeed/100,0);
	this->adjpos(0,vel[1] * terminalvel / 100);


}

void player::animate()
{//vars that change things inair,duck, aim, velocity,
	animationcounter += 1;
	if (animationcounter > 6) {
		animationcounter = 0;
		
		//cout << animationstate << ":" << vel[0]*aim[0] << endl;
		this->myanimations.nextframe();
		this->setupimage();
		if (myanimations.isend()) {
			animationloopcounter += 1;
		}

	}

	
	if (inair) {
		if (animationstate.compare("jumpinit")==0) {
			if (animationloopcounter > 0) {
				this->setanimation("midair");
			}
		}
		else if (animationstate.compare("midair")==0) {

		}
		else {
			this->setanimation("jumpinit");
		}
	}
	else if (duck) {
		if (abs(vel[0])>20) {
			this->setanimation("crawl");
		}
		else {
			this->setanimation("duckstill");
		}
	}
	else if (vel[0]!=0&&!inair) {
		if (vel[0] * aim[0] < 0 || (aim[0]==0&&abs(vel[0])>0)) {//stoping
			if (abs(vel[0]) > 60) {
				this->setanimation("endrun");
			}
			else {
				this->setanimation("idle");
			}
		}
		else if (abs(vel[0]) > 60) {//moving quickly
			this->setanimation("midrun");
		}
		else if (abs(vel[0]) > 0) {//slowleft
			this->setanimation("startrun");
		}
	}
	else if (vel[0] == 0 && !inair) {
		if (animationstate.compare("idle") == 0) {
			if (animationloopcounter > 10) {
				this->setanimation("startidle");
			}
		}
		else if (animationstate.compare("startidle") == 0) {
			if (animationloopcounter > 0) {
				this->setanimation("smokeloop");
			}
		}
		else if (animationstate.compare("smokeloop") == 0) {
			if (animationloopcounter > 4) {
				this->setanimation("resmoke");
			}
		}
		else if (animationstate.compare("resmoke") == 0) {
			if (animationloopcounter > 0) {
				this->setanimation("smokeloop");
			}
		}
		else {
			this->setanimation("idle");
		}
	}
	
	

	this->setupimagebox();

}

void player::setupimage()
{
	image = myanimations.getimage();
	rectangle im = myanimations.getImgBox();
	rectangle hit = myanimations.gethit();

	up = hit.bottom()-im.top();
	left = hit.centerx() - im.left();

	imagebox = hitbox(0,0,im.getW(),im.getH());
	this->setupimagebox();
}

void player::setupimagebox()
{
	if (!fliped) {
		imagebox.setx(collision.centerx() - left);
		imagebox.sety(collision.bottom() - up);
	}
	else {
		imagebox.setx(collision.centerx() - ((imagebox.right()-imagebox.left())-left));
		imagebox.sety(collision.bottom() - up);
	}
}

void player::setanimation(const char * name)
{
	if (string(name).compare(animationstate)) {
		animationstate = string(name);
		animationloopcounter = 0;
		if (animationstate.compare("idle") == 0) {
			myanimations.setanimation("idle");
		}
		else if (animationstate.compare("startidle") == 0) {
			myanimations.setanimation("toidle");
		}
		else if (animationstate.compare("smokeloop") == 0) {
			myanimations.setanimation("smokeloop");
		}
		else if (animationstate.compare("resmoke") == 0) {
			myanimations.setanimation("reidleloop");
		}
		else if (animationstate.compare("startrun") == 0) {
			myanimations.setanimation("startrun");
		}
		else if (animationstate.compare("midrun") == 0) {
			myanimations.setanimation("runloop");
		}
		else if (animationstate.compare("endrun") == 0) {
			myanimations.setanimation("stoprun");
		}
		else if (animationstate.compare("jumpinit") == 0) {
			myanimations.setanimation("jump");
		}
		else if (animationstate.compare("midair") == 0) {
			myanimations.setanimation("midair");
		}
		else if (animationstate.compare("duckstill") == 0) {
			myanimations.setanimation("crouch");
		}
		else if (animationstate.compare("crawl") == 0) {
			myanimations.setanimation("crawlloop");
		}
		this->setupimage();
	}
}

ALLEGRO_BITMAP * player::getAnimationImage()
{
	return image;
}

hitbox player::getAnimationBox()
{
	return imagebox;
}

void player::collisionWall(int left, int top, int right, int bottom)
{
	bool playeraim = false;
	int distances[4];//left top right bottom
	distances[0] = abs(left - this->collision.right());
	distances[1] = abs(top - this->collision.bottom());
	distances[2] = abs(right - this->collision.left());
	distances[3] = abs(bottom - this->collision.top());
	int choice = -1;
	if (aim[0]!=0 && !duck) {
		if(aim[1]==0){
			if (distances[1] < maxjumpvertical) {
				choice = 1;
			}
			else if (distances[3] < maxjumpvertical) {
				choice = 3;
			}
		}
		else {
			if (aim[1] == 1) {
				if (distances[1] < maxjumpvertical) {
					choice = 1;
				}
			}
			else {
				if (distances[3] < maxjumpvertical) {
					choice = 3;
				}
			}
		}
	}
	else if (aim[1] != 0) {
		if (aim[0] == 0) {
			if (distances[0] < maxjumphorizonal) {
				choice = 0;
			}
			else if (distances[2] < maxjumphorizonal) {
				choice = 2;
			}
		}
		else {
			if (aim[0] == 1) {
				if (distances[0] < maxjumphorizonal) {
					choice = 0;
				}
			}
			else {
				if (distances[2] < maxjumphorizonal) {
					choice = 2;
				}
			}
		}
	}

	if (choice == -1) {
		choice = 0;
		for (int i = 1; i < 4; i++) {
			if (distances[i] < distances[choice]) {
				choice = i;
			}
		}
	}

		
		
	//std::cout << "min"<< min << std::endl;
	switch (choice)
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

poly player::getdrawingbox()
{
	return imagebox.getdraw();
}

poly player::getdraw()
{
	return collision.getdraw();
}

bool player::getflip()
{
	return fliped;
}

bool player::isback()
{
	return shadow;
}

bool player::switchshadow()
{
	shadow = !shadow;
	return true;
}
