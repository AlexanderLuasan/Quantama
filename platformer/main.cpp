#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "level.h"
#include "display.h"
#include "player.h"
using namespace std;

int main() {
	cout << "hello world" << endl;
	system("pause");
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();

	level first("citymap.tmx");

	cout << first.getheight() << "  ";
	cout << first.getwidth();

	//system("pause");

	//player
	player hero = player(30, 30);
	hero.setupimage();
	
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;
	display screen(32*10, 32*6,4);
	al_install_keyboard();
	al_install_mouse();
//	screen = al_create_display(first.getwidth()*2, first.getheight()*2);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);
	al_start_timer(timer);

	al_register_event_source(queue, al_get_display_event_source(screen.gets()));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	int health = 100;
	bool controledge = false;

	bool running = true;
	int mx = 0, my = 0;
	while (running) {


		ALLEGRO_EVENT event;

		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {

			bool cover = false;
			for (int i = 0; i < first.cover.size(); i++) {
				if (first.cover[i].gethit().iswithin(hero.getcollision())) {
					cover = true;
					break;
				}
			}
			bool detected = false; 
			for (int i = 0; i < first.cams.size(); i++) {
				if (cover) {
					if (first.cams[i].background() != hero.isback()) {
						continue;
					}
				}
				if (first.cams[i].getcolision().collision(hero.getcollision())) {
					detected = true;
					break;
				}
			}
			cout << first.cover.size() <<"within: " << cover << " camdetection " << detected <<endl;

			ALLEGRO_KEYBOARD_STATE keys;
			al_get_keyboard_state(&keys);

			if (al_key_down(&keys, ALLEGRO_KEY_UP) && al_key_down(&keys, ALLEGRO_KEY_DOWN)) {
				hero.setyaim(0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_DOWN)) {
				hero.setyaim(1);
			}
			else if(al_key_down(&keys, ALLEGRO_KEY_UP)) {
				hero.setyaim(-1);
			}
			else {
				hero.setyaim(0);
			}
			if (al_key_down(&keys, ALLEGRO_KEY_LEFT)&& al_key_down(&keys, ALLEGRO_KEY_RIGHT)) {
				hero.setxaim(0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_LEFT)) {
				hero.setxaim(-1);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_RIGHT)) {
				hero.setxaim(1);
			}
			else {
				hero.setxaim(0);
			}
			if (al_key_down(&keys, ALLEGRO_KEY_SPACE)) {
				hero.setjump(true);
			}
			else {
				hero.setjump(false);
			}
			if (al_key_down(&keys, ALLEGRO_KEY_Z)) {
				if (!controledge) {
					hero.switchshadow();
				}
				controledge = true;
			}
			else {
				controledge = false;
			}
			hero.positionupdate();

			for (int i = 0; i < first.blocks.size(); i++) {
				if (first.blocks[i].gethit().collision(hero.getcollision())) {
					hero.collisionWall(first.blocks[i].gethit().left(hero.getcollision()), first.blocks[i].gethit().top(hero.getcollision()), first.blocks[i].gethit().right(hero.getcollision()), first.blocks[i].gethit().bottom(hero.getcollision()));
				}
			}
			hero.animate();
			screen.CamCenter(hero.getcollision().centerx(), hero.getcollision().centery());
			screen.drawstart();
			for (int i = 0; i < first.cams.size(); i++) {
 				first.cams[i].move();
			
			}
			plate background = first.getbg();
			plate foreground = first.getfg();
			//plate center = first.getct();

			//background
			screen.draw(background.draw(), 0, 0, background.getwidth(), background.getheight());
			//draw backimgs
			for (int i = 0; i < first.imgs.size(); i++) {
				rectangle box = first.imgs[i].getbox();

				screen.draw(first.imgs[i].getimg(), box.getX(), box.getY(), box.getW(), box.getH());
			}
			if (hero.isback()) {
				hitbox im = hero.getAnimationBox();
				screen.draw(hero.getdrawingbox());
				screen.draw(hero.getAnimationImage(), im.getx(), im.gety(), im.right() - im.getx(), im.bottom() - im.gety(), hero.getflip());
			}
			for (int i = 0; i < first.cams.size(); i++) {
				cammera d = first.cams[i];
				if (d.background()) {
					screen.drawview(d.getx(), d.gety(), d.getangle(), d.getanglesize(), d.getrange());
					screen.draw(d.getcolision().getdraw());
				}
			}
			//screen.draw(center.draw(), 0, 0, center.getwidth(), center.getheight());
			for (int i = 0; i < first.center.size(); i++) {
				rectangle box = first.center[i].getbox();
				screen.draw(first.center[i].getimg(), box.getX(), box.getY(), box.getW(), box.getH());
			}
			if (!hero.isback()) {
				hitbox im = hero.getAnimationBox();
				screen.draw(hero.getdrawingbox());
				screen.draw(hero.getAnimationImage(), im.getx(), im.gety(), im.right() - im.getx(), im.bottom() - im.gety(), hero.getflip());
			}
			for (int i = 0; i < first.cams.size(); i++) {
				cammera d = first.cams[i];
				if (!d.background()) {
					screen.drawview(d.getx(), d.gety(), d.getangle(), d.getanglesize(), d.getrange());
					screen.draw(d.getcolision().getdraw());
				}
			}



			for (int i = 0; i < first.front.size(); i++) {
				rectangle box = first.front[i].getbox();
				screen.draw(first.front[i].getimg(), box.getX(), box.getY(), box.getW(), box.getH());
			}


			for (int i = 0; i < first.blocks.size(); i++) {
				screen.draw(first.blocks[i].getdraw());
				int x = first.blocks[i].gethit().left(hero.getcollision());
				int y = first.blocks[i].gethit().top(hero.getcollision());
				int w = first.blocks[i].gethit().right(hero.getcollision());
				int h = first.blocks[i].gethit().bottom(hero.getcollision());
				screen.draw(x, y, w, h);

			}

			for (int i = 0; i < first.cover.size(); i++) {
				screen.draw(first.cover[i].getdraw());
				int x = first.cover[i].gethit().left(hero.getcollision());
				int y = first.cover[i].gethit().top(hero.getcollision());
				int w = first.cover[i].gethit().right(hero.getcollision());
				int h = first.cover[i].gethit().bottom(hero.getcollision());
				screen.draw(x, y, w, h);
			}
			screen.draw(hero.getdraw());
			screen.drawstealthbar(health);
			
			

			
			
			
			//draw background
			screen.draw(foreground.draw(), 0, 0, foreground.getwidth(), foreground.getheight());
			screen.drawview();
			al_flip_display();



		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {


		}


	}

	first.~level();
	al_destroy_display(screen.gets());
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	

	system("pause");
	return 0;
}