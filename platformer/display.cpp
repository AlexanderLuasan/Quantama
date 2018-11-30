#include "display.h"
#include <iostream>
display::display(int w, int h, int s)
{
	camx = 0;
	camy = 0;
	width = w;
	height = h;
	screen = al_create_display((width+2*globaladjust)*globalscale*s, (height+ 2*globaladjust)*globalscale*s);
	scale = s;

}

ALLEGRO_DISPLAY * display::gets()
{
	return screen;
}

void display::CamCenter(int x, int y)
{
	x -= width/2;
	y -= height/2;
	if (x > camx+64&&camax<maxcamspeed) {
		camax += 1;
	}
	else if (x < camx- 64 &&camax>-maxcamspeed) {
		camax -= 1;
	}
	else if (x > camx + 32 && camax<maxcamspeed/2) {
		camax += 1;
	}
	else if (x < camx - 32 && camax>-maxcamspeed/2) {
		camax -= 1;
	}
	else if(x > camx - 32 && x < camx + 32){
		if (camax > 0) {
			camax -= 1;
		}
		else if(camax<0) {
			camax += 1;
		}
	}

	if (y > camy + 64 && camay<maxcamspeed) {
		camay += 1;
	}
	else if (y < camy - 64 && camay>-maxcamspeed) {
		camay -= 1;
	}
	else if (y > camy + 32 && camay<maxcamspeed / 2) {
		camay += 1;
	}
	else if (y < camy - 32 && camay>-maxcamspeed / 2) {
		camay -= 1;
	}
	else if (y > camy - 32 && y < camy + 32) {
		if (camay > 0) {
			camay -= 1;
		}
		else if (camay<0) {
			camay += 1;
		}
	}

	this->adjCam(camax, camay);
}

bool display::setCam(int x, int y)
{
	camx = x;
	camy = y;
	return false;
}

bool display::adjCam(int x, int y)
{
	camx = camx + x;
	camy = camy + y;
	return false;
}

bool display::drawstart()
{
	al_set_target_backbuffer(screen);
	al_clear_to_color(al_map_rgb(50, 50, 50));
	return false;
}

bool display::drawview()
{
	al_draw_rectangle(scale*(0+ globaladjust), scale*(0+ globaladjust), scale*(width+ globaladjust), scale*(height+ globaladjust),al_map_rgb(0,0,0),4);
	return false;
}

bool display::draw(ALLEGRO_BITMAP * image, int x, int y, int w, int h)
{

	int sx, sy, sw, sh;
	int dx, dy, dw, dh;
	if (x < camx) {//off left on screen
		sx = camx - x;
		dx = 0;
	}
	else {
		sx = 0;
		dx = x - camx;
	}
	
	if (y < camy) {
		sy = camy - y;
		dy = 0;
	}
	else {
		sy = 0;
		dy = y - camy;
	}

	if (camx + width < x + w) {
		sw = (w-sx)-((x+w)-(camx+width));
		dw = (w-sx)- ((x + w) - (camx + width));

	}
	else {
		sw = w-sx;
		dw = w-sx;
		if (x + w < camx) {
			dw = 0;
		}
	}
	if (camy + height < y + h) {
		sh = h - ((y + h) - (camy + height))- camy;
		dh = h - ((y + h) - (camy + height))- camy;

	}
	else {
		sh = h-sy;
		dh = h-sy;
		if (y + h < camy) {
			dh = 0;
		}
	}

	if (dw <= 0 || dh <= 0) {
		return false;
	}

	al_draw_scaled_bitmap(image,sx,sy,sw,sh,scale*(dx+ globaladjust),scale*(dy+ globaladjust),scale*(dw),scale*(dh),0);



	return true;
}

bool display::draw(ALLEGRO_BITMAP * image, int x, int y, int w, int h, bool flip)
{
	int sx, sy, sw, sh;
	int dx, dy, dw, dh;
	if (x < camx) {//off left on screen
		sx = camx - x;
		dx = 0;
	}
	else {
		sx = 0;
		dx = x - camx;
	}

	if (y < camy) {
		sy = camy - x;
		dy = 0;
	}
	else {
		sy = 0;
		dy = y - camy;
	}

	if (camx + width < x + w) {
		sw = w - ((x + w) - (camx + width));
		dw = w - ((x + w) - (camx + width));

	}
	else {
		sw = w;
		dw = w;
		if (x + w < camx) {
			dw = 0;
		}
	}
	if (camy + height < y + h) {
		sh = h - ((y + h) - (camy + height));
		dh = h - ((y + h) - (camy + height));

	}
	else {
		sh = h;
		dh = h;
		if (y + h < camy) {
			dh = 0;
		}
	}

	if (dw <= 0 || dh <= 0) {
		return false;
	}
	if (flip) {
		al_draw_scaled_bitmap(image, sx, sy, sw, sh, scale*(dx + globaladjust), scale*(dy + globaladjust), scale*(dw), scale*(dh), ALLEGRO_FLIP_HORIZONTAL);
	}
	else {
		al_draw_scaled_bitmap(image, sx, sy, sw, sh, scale*(dx + globaladjust), scale*(dy + globaladjust), scale*(dw), scale*(dh),0);
	}
	return true;
}

bool display::draw(poly shape)
{
	int x, y;
	x = shape.getPosx();
	y = shape.getPosy();
	int x1, x2, y1, y2;
	for (int i = 0; i < shape.getsize()-1; i++) {
		x1 = shape.xpoint(i);
		x2 = shape.xpoint(i+1);
		y1 = shape.ypoint(i);
		y2 = shape.ypoint(i+1);
		al_draw_line(scale*(x+x1+globaladjust- camx), scale*(y + y1 + globaladjust-camy), scale*(x + x2 + globaladjust-camx), scale*(y + y2 + globaladjust-camy),al_map_rgb(0,0,0),4);
	}
	x1 = shape.xpoint(0);
	x2 = shape.xpoint(shape.getsize() - 1);
	y1 = shape.ypoint(0);
	y2 = shape.ypoint(shape.getsize() - 1);
	al_draw_line(scale*(x + x1 + globaladjust - camx), scale*(y + y1 + globaladjust - camy), scale*(x + x2 + globaladjust - camx), scale*(y + y2 + globaladjust - camy), al_map_rgb(0, 0, 0), 4);
	return false;
}

bool display::draw(int x, int y, int w, int h)
{
	al_draw_rectangle(scale*(x-camx + globaladjust), scale*(y-camy + globaladjust),scale*( w-camx + globaladjust),scale*( h-camy+globaladjust),al_map_rgb(0,0,0),2);
	return false;
}

bool display::drawview(int x, int y, double angle, double size, int range)
{
	
	int x2 = (double(x) + cos(angle + size)*range) - camx+globaladjust;
	int y2 = (double(y) + sin(angle + size)*range) - camy + globaladjust;

	int x3 = (double(x) + cos(angle - size)*range) - camx + globaladjust;
	int y3 = (double(y) + sin(angle - size)*range) - camy + globaladjust;
	x = x - camx + globaladjust;
	y = y - camy + globaladjust;
	al_draw_filled_triangle(x*scale,y*scale,x2*scale,y2*scale,x3*scale,y3*scale,al_map_rgba(125,0,125,125));

	return true;
}

bool display::drawstealthbar(int percent)
{
	int bar = width * barsize / 100;
	al_draw_filled_rectangle(scale*bar / 2, 2, scale * bar / 2 + scale * bar*percent/100,scale * height/10,al_map_rgb(0,125,0));
	al_draw_rectangle(scale * bar/2,2,scale * width-scale * bar/2,scale * height/10,al_map_rgb(0,0,0),4);

	return true;
}
