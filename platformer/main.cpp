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

			}
			else if (al_key_down(&keys, ALLEGRO_KEY_DOWN)) {
				hero.adjpos(0, 1);
			}
			else if(al_key_down(&keys, ALLEGRO_KEY_UP)) {
				hero.adjpos(0, -1);
			}
			if (al_key_down(&keys, ALLEGRO_KEY_LEFT)&& al_key_down(&keys, ALLEGRO_KEY_RIGHT)) {

			}
			else if (al_key_down(&keys, ALLEGRO_KEY_LEFT)) {
				hero.adjpos(-1, 0);
			}
			else if (al_key_down(&keys, ALLEGRO_KEY_RIGHT)) {
				hero.adjpos(1, 0);
			}






			screen.drawstart();
			plate backgound = first.getbg();


			screen.drawview();
			screen.draw(backgound.draw(), 0, 0, backgound.getwidth(), backgound.getheight());
			for (int i = 0; i < first.blocks.size(); i++) {
				screen.draw(first.blocks[i].getdraw());
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