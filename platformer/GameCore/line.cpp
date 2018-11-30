#include "line.h"



	linecoll::linecoll(int x1, int y1, int x2, int y2)
	{
		slopey = y1 - y2;
		slopex = x1 - x2;
		if (x1 > x2) {
			this->setX(x2);
			this->setW(x1 - x2);
			if (y1 < y2) {

				this->setY(y1);
				this->setH(y2 - y1);
			}
			else {
				this->setY(y2);
				this->setH(y1 - y2);
			}
		}
		else {
			this->setX(x1);
			this->setW(x2 - x1);
			if (y1 < y2) {
				this->setY(y1);
				this->setH(y2 - y1);
			}
			else {
				this->setY(y2);
				this->setH(y1 - y2);
			}
		}
	}

	bool linecoll::Collision(collisionobj * other)
	{
		int pos;
		int value;
		if (this->right()>other->left()) {
			pos = other->left()-this->left();
			if (slopex != 0) {
				value = pos * slopey / slopex;
			}
			else {
				value = 1000;
			}
			if (this->getY() + value > other->top() && this->getY() + value < other->bottom()) {
				return true;
			}
		}
		if (this->left() < other->right()) {
			pos = this->left()-other->right();
			if (slopex != 0) {
				value = pos * slopey / slopex;
			}
			else {
				value = 1000;
			}
			if (this->getY() + value > other->top() && this->getY() + value < other->bottom()) {
				return true;
			}
		}
		if (this->bottom()>other->top()) {
			pos = other->top() - this->top();
			if (slopey != 0) {
				value = pos * slopex / slopey;
			}
			else {
				value = 1000;
			}
			if (this->getX() + value > other->left() && this->getX() + value < other->right()) {
				return true;
			}
		}
		if (this->top() < other->bottom()) {
			pos = this->top() - other->bottom();
			if (slopey != 0) {
				value = pos * slopex / slopey;
			}
			else {
				value = 1000;
			}
			if (this->getX() + value > other->left() && this->getX() + value < other->right()) {
				return true;
			}
		}
		return false;

	}
	poly linecoll::getdraw()
	{
		poly end = poly(this->getX(), this->getY());
		if (slopex < 0 && slopey < 0) {
			end.addpoint(0, 0);
			end.addpoint(this->getW(), this->getH());
		}
		else if (slopex > 0 && slopey > 0) {
			end.addpoint(0, 0);
			end.addpoint(this->getW(), this->getH());
		}
		else {
			end.addpoint(this->getW(), 0);
			end.addpoint(0, this->getH());
		}

		return end;
	}
