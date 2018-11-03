#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "level.h"
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


	ALLEGRO_DISPLAY * screen;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;

	al_install_keyboard();
	al_install_mouse();
	screen = al_create_display(first.getwidth()*2, first.getheight()*2);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);
	al_start_timer(timer);

	al_register_event_source(queue, al_get_display_event_source(screen));
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






			al_set_target_backbuffer(screen);
			al_clear_to_color(al_map_rgb(0, 255, 255));
			plate backgound = first.getbg();
			al_draw_circle(10, 10, 40, al_map_rgb(0, 0, 0), 4);
			al_draw_bitmap(backgound.draw(), 0, 0, 0);

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