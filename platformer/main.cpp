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
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();

	level first("map.tmx");

	cout << first.getheight() << "  ";
	cout << first.getwidth();

	system("pause");

	//player
	player hero = player(30, 30);

	
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;
	display screen(first.getwidth(), first.getheight(),2);
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



	bool running = true;
	int mx = 0, my = 0;
	while (running) {


		ALLEGRO_EVENT event;

		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER) {




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
			hero.positionupdate();

			for (int i = 0; i < first.blocks.size(); i++) {
				if (first.blocks[i].gethit().collision(hero.getcollision())) {
					hero.collisionWall(first.blocks[i].gethit().left(hero.getcollision()), first.blocks[i].gethit().top(hero.getcollision()), first.blocks[i].gethit().right(hero.getcollision()), first.blocks[i].gethit().bottom(hero.getcollision()));
				}
			}



			screen.drawstart();
			plate backgound = first.getbg();


			screen.drawview();
			screen.draw(backgound.draw(), 0, 0, backgound.getwidth(), backgound.getheight());
			for (int i = 0; i < first.blocks.size(); i++) {
				screen.draw(first.blocks[i].getdraw());
				int x = first.blocks[i].gethit().left(hero.getcollision());
				int y = first.blocks[i].gethit().top(hero.getcollision());
				int w = first.blocks[i].gethit().right(hero.getcollision());
				int h = first.blocks[i].gethit().bottom(hero.getcollision());
				//screen.draw(x, y, w, h);
				if (first.blocks[i].getImage() != nullptr) {
					screen.draw(first.blocks[i].getImage(), x, y, w-x, h-y);
				}
			}
			screen.draw(hero.getdraw());
			al_flip_display();



		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {


		}


	}












	system("pause");
	return 0;
}