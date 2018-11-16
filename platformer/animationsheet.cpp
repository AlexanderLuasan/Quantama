#include "animationsheet.h"

#include <iostream>

animation::animation()
{
}

void animation::addframe(rectangle image, rectangle hit)
{
	images.push_back(image);
	hitbox.push_back(hit);
}

rectangle animation::getimg(int index)
{
	return images[index];
}

rectangle animation::gethit(int index)
{
	return hitbox[index];
}

int animation::frames()
{
	return images.size();
}

animationset::animationset()
{
}

animationset::animationset(string pathtodoc)
{
	frame = 0;
	animationindex = 0;
	tmxtag file = tmxtag((string(pathtofiles)+pathtodoc).c_str(),0);
	
	for (int i = 0; i < file.tagcount(); i++) {
		tmxtag currentlayer = file.get(i);
		
		if (currentlayer.head("type").compare("tileset")==0) {
			string image = currentlayer.get(0).head("source");
			sheet = al_load_bitmap((string(pathtofiles) + image).c_str());
		}
		else if (currentlayer.head("type").compare("objectgroup")==0) {
			animationnames.push_back(currentlayer.head("name"));

			animations.push_back(animation());

			this->decode(currentlayer, animations.size() - 1);

		}


	}

}

void animationset::decode(tmxtag group, int locationinarr)
{

	int index = -1;
	while (true) {
		index++;
		int img;
		int hit;
		bool found = false;
		for (img = 0; img < group.tagcount(); img++) {
			if (group.get(img).head("name").compare(string("img") + to_string(index))==0) {
				found = true;
				break;
			}
		}
		
		for (hit = 0; hit < group.tagcount(); hit++) {
			if (group.get(hit).head("name").compare(string("hit") + to_string(index))==0) {
				found = true;
				break;
			}
		}

		if (found) {
			int x1, x2, y1, y2, w1, w2, h1, h2;
			x1 = stoi(group.get(img).head("x"));
			y1 = stoi(group.get(img).head("y"));
			w1 = stoi(group.get(img).head("width"));
			h1 = stoi(group.get(img).head("height"));
			x2 = stoi(group.get(hit).head("x"));
			y2 = stoi(group.get(hit).head("y"));
			w2 = stoi(group.get(hit).head("width"));
			h2 = stoi(group.get(hit).head("height"));
			animations[locationinarr].addframe(rectangle(x1,y1,w1,h1), rectangle(x2, y2, w2, h2));
		}
		else {
			break;
		}
	}

}

void animationset::setanimation(string nameofanimation)
{
	for (int i = 0; i < animationnames.size(); i++) {
		if (animationnames[i].compare(nameofanimation) == 0) {
			animationindex = i;
			frame = frame % animations[animationindex].frames();
			return;
		}
	}
	animationindex = 0;
	frame = frame % animations[animationindex].frames();
}

void animationset::nextframe()
{
	frame += 1;
	frame = frame % animations[animationindex].frames();
}

ALLEGRO_BITMAP * animationset::getimage()
{

	rectangle box = animations[animationindex].getimg(frame);

	return al_create_sub_bitmap(sheet,box.getX(), box.getY(), box.getW(), box.getH());
}

rectangle animationset::gethit()
{
	return animations[animationindex].gethit(frame);
}

rectangle animationset::getImgBox()
{
	return animations[animationindex].getimg(frame);
}
