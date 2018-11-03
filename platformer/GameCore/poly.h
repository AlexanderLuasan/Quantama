#pragma once






class poly
{
public:
	poly(int x,int y);
	void addpoint(int x,int y);
	int getsize();
	int xpoint(int index);
	int ypoint(int index);
	int getPosx();
	int getPosy();

private:
	int xpos;
	int ypos;

	int xs[10];
	int ys[10];
	int index;
};

