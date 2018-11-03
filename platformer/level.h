#pragma once
#include "GameCore/tiledparser.h"
#include "GameCore/hitbox.h"
#include "GameCore/plate.h"
#include "GameCore/tilesheet.h"
#include <string>
#include <vector>
class level
{
public:
	level();
	level(string levelname);

	//setupdiv

	void handletilesheets(tmxtag currentlayer);

	void handleplates(tmxtag currentlayer);
	bool addfg(int tile,int x, int y);
	bool addbg(int tile, int x, int y);

	int getwidth();
	int getheight();

	//extracting

	plate getbg();
private:


	int tileheight;
	int tilewidth;
	int width;
	int height;

	vector<sheet> tilesheets;

	plate fg;
	plate bg;


};


