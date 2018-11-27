#include "triangle.h"
#include <iostream>
using namespace std;
int triangle::id()
{


	return 3;
}

triangle::triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int mx;
	int my;
	int minx;
	int miny;
	int maxx;
	int maxy;
	int xs[3] = { x1,x2,x3 };
	int ys[3] = { y1,y2,y3 };
	minx = xs[0];
	maxx = xs[0];
	miny = ys[0];
	maxy = ys[0];


	for (int i = 0; i < 3; i++) {
		if (xs[i] > maxx) {
			maxx = xs[i];
		}
		if (xs[i] < minx) {
			minx = xs[i];
		}


		if (ys[i] > maxy) {
			maxy = ys[i];
		}
		if (ys[i] < miny) {
			miny = ys[i];
		}
	}


	this->setX(minx);
	this->setY(miny);
	this->setW(maxx - minx);
	this->setH(maxy - miny);
	
	slope = false;
	for (int i = 0; i < 3; i++) {
		for (int ii = 0; ii < 3; ii++) {
			if (i != ii) {
				if (xs[i] == xs[ii]) {
					mx = xs[i];
				}
				else if (ys[i] == ys[ii]) {
					my = ys[i];
				}
			}
			else {
				if (xs[i] == minx && ys[i] == miny) {
					slope = true;
				}
			}
		}
	}
	if (slope) {
		if (mx == this->getX()) {
			down = true;
		}
		else {
			down = false;
		}
	}
	else {
		if (mx == this->getX()) {
			down = false;
		}
		else {
			down = true;
		}
	}
}

poly triangle::getdraw()
{
	poly end = poly(this->getX(), this->getY());
	if (slope) {
		end.addpoint(0, 0);
		end.addpoint(this->getW(), this->getH());
		if (down) {
			end.addpoint(0, this->getH());
		}
		else {
			end.addpoint(this->getW(), 0);
		}
	}
	else {
		end.addpoint(this->getW(), 0);
		end.addpoint(0, this->getH());
		if (down) {
			end.addpoint(this->getW(), this->getH());
		}
		else {
			end.addpoint(0, 0);
		}
	}
	return end;
}

int triangle::leftR(collisionobj * other)
{
	if (slope == true && down == true) {
		return this->left();
	}
	else if (slope == false && down == false) {
		return this->left();
	}

	int pos;
	if (!slope) {
		pos = this->bottom() - other->bottom();
	}
	else {
		pos = other->top() - this->top();
	}


	int end = this->left() - (double(-this->getW()) / this->getH() * pos);
	if (end<this->left() || end>this->right()) {
		end = this->left();
	}
	return end;
}

int triangle::rightR(collisionobj * other)
{
	if (slope == false && down == true) {
		return this->right();
	}
	else if (slope == true && down == false) {
		return this->right();
	}
	int pos;
	if (slope) {
		pos = other->bottom() - this->bottom();
	}
	else {
		pos = this->top()-other->top();
	}

	int end = this->right() + (double(this->getW()) / this->getH() * pos);
	if (end<this->left() || end>this->right()) {
		end = this->right();
	}
	return end;
	
}

int triangle::bottomR(collisionobj * other)
{
	if (slope == false && down == true) {
		return this->bottom();
	}
	else if (slope == true && down == true) {
		return this->bottom();
	}
	int pos;
	if (!slope) {
		pos = other->left()- this->left();
	}
	else {
		pos = this->right()-other->right();
	}
	int end = this->bottom() + double(this->getH()) / this->getW()*pos;
	if (end > this->bottom() || end < this->top()) {
		return this->bottom();
	}

	return end;
}

int triangle::topR(collisionobj * other)
{
	if (slope == true && down == false) {
		return this->top();
	}
	else if (slope == false && down == false) {
		return this->top();
	}
	int pos;
	if (slope) {
		pos = other->left()-this->left();
	}
	else {
		pos = this->right() - other->right();
	}

	int end = this->top() + double(this->getH()) / this->getW()*pos;
	if (end > this->bottom() || end < this->top()) {
		return this->top();
	}
	return end;
}
