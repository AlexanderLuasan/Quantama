#pragma once
#include <allegro5/allegro.h>
#include <string>
#include "GameCore/tiledparser.h"
#include <vector>

#define imgpath  "./images/"
using namespace std;
class square
{
public:
	square();
	square(string n,int x,int y,int w,int h);

	string getname();
	int getw();
	int getx();
	int gety();
	int geth();

private:
	string name;
	int x, y, width, height;

};

class sheetlist 
{
public:
	sheetlist();
	sheetlist(string name);
	bool add(tmxtag obj);
	ALLEGRO_BITMAP * getimage(string name);


private:
	ALLEGRO_BITMAP * sheet;
	vector<square> images;
	

};

