#pragma once
#include "GameCore/tiledparser.h"
#include "GameCore/rect.h"
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#define pathtofiles "./images/"
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
	animationset();
	animationset(string pathtodoc);
	void decode(tmxtag group, int index);


	void setanimation(string nameofanimation);
	void nextframe();
	bool isend();

	ALLEGRO_BITMAP * getimage();
	rectangle gethit();
	rectangle getImgBox();
	 
private:
	bool end;
	int animationindex;
	int frame;
	vector<animation> animations;
	ALLEGRO_BITMAP * sheet;
	vector<string> animationnames;
	

};
