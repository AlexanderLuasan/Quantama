#include "nonuniformartsheet.h"

square::square()
{
	x = 0;
	y = 0;
	width = 10;
	height = 10;
}

square::square(string n,int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->height = h;
	this->width = w;
	this->name = n;
}

string square::getname()
{
	return name;
}

int square::getw()
{
	return width;
}

int square::getx()
{
	return x;
}

int square::gety()
{
	return y;
}

int square::geth()
{
	return height;
}

sheetlist::sheetlist()
{
}

sheetlist::sheetlist(string name)
{
	tmxtag file = tmxtag(name,1);

	for (int i = 0; i < file.tagcount(); i++) {
		tmxtag current = file.get(i);

		if (current.head("type").compare("objectgroup") == 0) {
			for (int ii = 0; ii < current.tagcount(); ii++) {
				add(current.get(ii));
			}
		}
		else if (current.head("type").compare("tileset") == 0) {

			string imgname = current.get(0).head("source");
			sheet = al_load_bitmap((string(imgpath)+imgname).c_str());
		}
	}


}

bool sheetlist::add(tmxtag obj)
{
	
	int x = stoi(obj.head("x"));
	int y = stoi(obj.head("y"));
	int w = stoi(obj.head("width"));
	int h = stoi(obj.head("height"));

	string name = obj.head("name");
	
	images.push_back(square(name, x, y, w, h));
	return false;
}

ALLEGRO_BITMAP * sheetlist::getimage(string name)
{
	for (int i = 0; i < images.size(); i++) {
		if (name.compare(images[i].getname())==0) {
			return al_create_sub_bitmap(sheet,images[i].getx(),images[i].gety(),images[i].getw(),images[i].geth());
		}
	}
	return nullptr;
}
