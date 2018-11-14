#include "animationsheet.h"

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

void animationset::setanimation(string nameofanimation)
{
	for (int i = 0; i < animationnames.size(); i++) {
		if (animationnames[i].compare(nameofanimation) == 0) {
			animation = i;
			return;
		}
	}
	animation = 0;
}

void animationset::nextframe()
{
	frame += 1;
}
