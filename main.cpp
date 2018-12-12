#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Game.h"

/*
   written by zia, ziabadar4991@gmail.com
*/

int main(int argc, char *argv[])
{
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_DISPLAY* display = al_create_display(570, 660);
	ALLEGRO_TIMER* timer = al_create_timer(1.0/60.0);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	Game game;
	game.load_map_from_file();
	game.set_timer(timer);

	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);
	bool redraw = true;
	bool exit = false;
	while(!exit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER || ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			al_clear_to_color(al_map_rgb(20, 20, 20));
			game.update(&ev);
			redraw = true;
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) exit = true;
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			al_flip_display();
			redraw = false;
		}

	}

	return 0;
}
