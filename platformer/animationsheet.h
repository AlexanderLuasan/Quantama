#pragma once
#include "GameCore/tiledparser.h"
#include "GameCore/rect.h"
#include <vector>
#include <string>
#include <allegro5/allegro.h>
using namespace std;



class animation 
{
public:
	animation();
	void addframe(rectangle image, rectangle hit);
	rectangle getimg(int index);
	rectangle gethit(int index);
	int frames();
private:
	vector<rectangle>images;
	vector<rectangle>hitbox;
};



class animationset
{

public:


	void setanimation(string nameofanimation);
	void nextframe();

	

private:
	int animation;
	int frame;
	vector<int> animations;
	ALLEGRO_BITMAP * sheet;
	vector<string> animationnames;
	

};
