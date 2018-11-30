#pragma once
#include "GameCore/tiledparser.h"
#include "GameCore/hitbox.h"
#include "GameCore/plate.h"
#include "GameCore/tilesheet.h"
#include "nonuniformartsheet.h"
#include "zone.h"
#include <string>
#include <vector>
#include "art.h"
#include "camera.h"
class level
{
public:
	level();
	~level();
	level(string levelname);

	//setupdiv

	void handletilesheets(tmxtag currentlayer);

	void handleplates(tmxtag currentlayer);
	bool addfg(int tile,int x, int y);
	bool addbg(int tile, int x, int y);
	bool addct(int tile, int x, int y);


	void handlezones(tmxtag currentlayer);
	ALLEGRO_BITMAP * artsearch(string name);
	bool maketriangle(tmxtag obj);
	bool makecircle(tmxtag obj);
	bool rectangle(tmxtag obj);
	void handleactors(tmxtag currentlayer);
	bool makecammera(tmxtag obj);
	propertyholder decode(tmxtag list);

	int getwidth();
	int getheight();

	//extracting
	vector<zone> blocks;
	vector<zone> cover;

	vector<art> imgs;
	vector<art> center;
	vector<art> front;

	vector<cammera> cams;
	
	plate getbg();
	plate getct();
	plate getfg();
private:
	

	int tileheight;
	int tilewidth;
	int width;
	int height;

	vector<sheet> tilesheets;
	vector<sheetlist> imagesheets;
	plate fg;
	plate ct;
	plate bg;

	


};


