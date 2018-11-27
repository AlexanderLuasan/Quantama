#pragma once
#include "propertiesholder.h"
#include "GameCore/hitbox.h"


class zone
{
public:
	zone();
	zone(hitbox hit, propertyholder data);
	hitbox gethit();
	propertyholder getdata();
	poly getdraw();

private:
	propertyholder mydata;
	hitbox collision;



};