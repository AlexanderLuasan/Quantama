#include "level.h"
#include <iostream>


#define path "./images/"
#define impath "./images/"

using namespace std;
level::level()
{
}

level::level(string levelname)
{

	imagesheets.push_back(sheetlist(string(path) + "firstunsizedtiles.tmx"));

	tmxtag file = tmxtag(string(path) + levelname,0);

	

	tileheight = stoi(file.head("tileheight"));
	tilewidth = stoi(file.head("tilewidth"));
	height = stoi(file.head("height"))*tileheight;
	width = stoi(file.head("width"))*tilewidth;
	
	bg = plate(width, height);
	fg = plate(width, height);


	for (int layers = 0; layers < file.tagcount(); layers++) {
		tmxtag currentlayer = file.get(layers);

		//tilesheets
		if (currentlayer.head("type").compare("tileset")==0) {
			this->handletilesheets(currentlayer);

		}
		//plates / layers
		else if (currentlayer.head("type").compare("layer")==0) {
			this->handleplates(currentlayer);
		}
		else if (currentlayer.head("type").compare("objectgroup") == 0) {
			if (currentlayer.head("name").compare("zones") == 0) {
				handlezones(currentlayer);
			}
			else if (currentlayer.head("name").compare("actors") == 0) {
				handleactors(currentlayer);
			}
		}
		else {

		}
	}





}


void level::handletilesheets(tmxtag currentlayer)
{

	if (currentlayer.head("type").compare("tileset") == 0) {
		tmxtag img = currentlayer.get(0);

		int tileheight = stoi(currentlayer.head("tileheight"));
		int tilewidth = stoi(currentlayer.head("tilewidth"));
		int count = stoi(currentlayer.head("tilecount"));
		int horizontalwidth = stoi(currentlayer.head("columns"));

		string imgname = img.head("source");
		tilesheets.push_back(sheet(string(string(impath) + imgname).c_str(), 0, tilewidth, tileheight,horizontalwidth, count / horizontalwidth));

	}
}

void level::handleplates(tmxtag currentlayer)
{
	int w = stoi(currentlayer.head("width"));
	int h = stoi(currentlayer.head("height"));
	string initdata = currentlayer.get(0).getData();
	int x = -1;
	int y = 0;
	bool backgound = currentlayer.head("name").find("bg") != string::npos;
	if (true) {
		for (int end = 0; end < initdata.size(); end++) {
			if (initdata[end] == ',' || initdata[end] == '\n') {
				x += 1;
				int tile = stoi(initdata.substr(0, end));
				if (backgound) {
					this->addbg(tile, x, y);
				}
				else {
					this->addfg(tile, x, y);
				}


				break;
			}

		}

		for (int i = 0; i < initdata.size(); i++) {
			x += 1;
			if (x > w) {
				y += 1;
				x = 0;
				cout << endl;
			}
			int start;
			int end;
			for (start = i; start < initdata.size(); start++) {
				if (initdata[start] == ',' || initdata[start] == '\n') {
					break;
				}

			}
			for (end = start + 1; end < initdata.size(); end++) {
				if (initdata[end] == ',' || initdata[end] == '\n') {
					break;
				}

			}
			i = end - 1;
			if (0!= end - start - 1) {
				int tile = stoi(initdata.substr(start + 1, end - start - 1));

				if (backgound) {
					this->addbg(tile, x, y);
				}
				else {
					this->addfg(tile, x, y);
				}
			}
		}
	}

}

bool level::addbg(int tile, int x, int y)
{
	if (tile > 0) {
		tile -= 1;
		int currentsheet = 0;
		while (currentsheet < tilesheets.size()) {
			if (tile < tilesheets[currentsheet].getcount()) {
				bg.addtile(tilesheets[currentsheet].getar(tile), x*tilewidth, y*tileheight, tilesheets[currentsheet].getw(), tilesheets[currentsheet].geth());
				return true;
			}
			tile -= tilesheets[currentsheet].getcount();
			currentsheet += 1;
		}
		bg.addtile(tilesheets[0].getar(tile), x * 16, y * 16, 16, 16);
	}
	return false;
}



bool level::addfg(int tile, int x, int y)
{
	if (tile > 0) {
		tile -= 1;
		int currentsheet = 0;
		while (currentsheet < tilesheets.size()) {
			if (tile < tilesheets[currentsheet].getcount()) {
				fg.addtile(tilesheets[currentsheet].getar(tile), x*tilewidth, y*tileheight, tilesheets[currentsheet].getw(), tilesheets[currentsheet].geth());
				return true;
			}
			tile -= tilesheets[currentsheet].getcount();
			currentsheet += 1;
		}
	}
	return false;
}



void level::handlezones(tmxtag currentlayer)
{
	bool cir;
	for (int i = 0; i < currentlayer.tagcount();i++) {
		tmxtag obj = currentlayer.get(i);
		if (obj.head("width").compare("none") == 0) {//tirangle
			maketriangle(obj);
		}
		else {
			cir = false;
			for (int ii = 0; ii < obj.tagcount(); ii++) {
				if (obj.get(ii).head("type").compare("ellipse")==0) {
					makecircle(obj);
					cir = true;
				}
			}
			if (cir == false) {
				rectangle(obj);
			}
		}
	}
}

ALLEGRO_BITMAP * level::artsearch(string name)
{
	for (int i = 0; i < imagesheets.size(); i++) {
		if (imagesheets[i].getimage(name) != nullptr) {
			return imagesheets[i].getimage(name);
		}
	}
	cout << "help";

}

bool level::maketriangle(tmxtag obj)
{
	int x = stoi(obj.head("x"));
	int y = stoi(obj.head("y"));
	hitbox tri;
	propertyholder prop;
	int nums[6];
	string point;
	for (int i = 0; i < obj.tagcount(); i++) {
		if (obj.get(i).head("type").compare("polygon")==0) {
			point = obj.get(i).head("points");
			int s, e;
			
			for (int ii = 0; ii < 5; ii++) {
				s = 0;
				if (point.find(',') < point.find(' ')) {
					e = point.find(',');
				}
				else {
					e= point.find(' ');
				}

				nums[ii] = stoi(point.substr(s, e - s));
				point = point.substr(e+1);
				
			}
			nums[5] = stoi(point.substr(s));
			tri = hitbox(x+nums[0],y+nums[1],x+ nums[2], y+nums[3], x+nums[4],y+ nums[5]);

		}
		else if(obj.get(i).head("type").compare("properties")==0) {
			prop = decode(obj.get(i));
		}
	}
	blocks.push_back(zone(tri,prop));


	return false;
}

bool level::makecircle(tmxtag obj)
{
	int x = stoi(obj.head("x"));
	int y = stoi(obj.head("y"));
	int radius = stoi(obj.head("width")) / 2;

	hitbox cir = hitbox(x+radius,y+radius,radius);
	propertyholder prop;
	string point;
	for (int i = 0; i < obj.tagcount(); i++) {
		if (obj.get(i).head("type").compare("properties") == 0) {
			prop = decode(obj.get(i));
		}
	}
	blocks.push_back(zone(cir, prop));
	return false;
}

bool level::rectangle(tmxtag obj)
{
	int x = stoi(obj.head("x"));
	int y = stoi(obj.head("y"));
	int w = stoi(obj.head("width"));
	int h = stoi(obj.head("height"));
	hitbox rec = hitbox(x, y, w,h);
	propertyholder prop;
	string point;
	art image;
	for (int i = 0; i < obj.tagcount(); i++) {
		if (obj.get(i).head("type").compare("properties") == 0) {
			prop = decode(obj.get(i));
		}
	}
	if (prop.isin("image")) {
		image = art(this->artsearch(prop.get("image")),x,y,w,h);
		imgs.push_back(image);
	}
	zone end = zone(rec, prop);
	
	blocks.push_back(end);
	return false;
}

void level::handleactors(tmxtag currentlayer)
{
	for (int i = 0; i < currentlayer.tagcount(); i++) {
		tmxtag actor = currentlayer.get(i);

		if (actor.head("name").compare("cammera") == 0) {
			makecammera(actor);
		}
	
	}

}

bool level::makecammera(tmxtag obj)
{
	propertyholder prop;
	for (int i = 0; i < obj.tagcount(); i++) {
		if (obj.get(i).head("type").compare("properties") == 0) {
			prop = decode(obj.get(i));
		}
	}
	int x = stoi(obj.head("x"));
	int y = stoi(obj.head("y"));
	int range = stoi(prop.get("range"));
	double cone = stod(prop.get("cone"));
	double center = stod(prop.get("center"));
	double size = stod(prop.get("size"));
	double speed = stod(prop.get("speed"));
	cammera actor = cammera(x,y,range,cone,center,size,speed);
	cams.push_back(actor);
	return true;
}

propertyholder level::decode(tmxtag list)
{
	propertyholder end = propertyholder();
	for (int i = 0; i < list.tagcount(); i++) {
		end.add(list.get(i).head("name"), list.get(i).head("value"));
	}

	return end;
}

int level::getwidth()
{
	return width;
}

int level::getheight()
{
	return height;
}

plate level::getbg(){return bg;}

plate level::getfg()
{
	return fg;
}
