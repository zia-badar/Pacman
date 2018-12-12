#ifndef PACMAN_H
#define PACMAN_H

#include <cmath>
#include <allegro5/allegro.h>

#include "Waypoint.h"

class Pacman
{
	public:
		Waypoint waypoint;
		Waypoint* source;
		Waypoint* destination;

		int scale_size = 20;
		ALLEGRO_BITMAP* pacman_bitmap;
		ALLEGRO_TIMER *timer;
		int start_time = 0;
		int speed = 3;

		Pacman();
		void move(vec2 direction);
		void jump_to(Waypoint* s, Waypoint* d);
};

#endif
