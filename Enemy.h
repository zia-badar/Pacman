#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>

#include "vec2.h"
#include "Waypoint.h"

class Enemy
{
	public:
		vec2 position;
		Waypoint* closest_waypoint_to_pacman;

		int scale_size = 20;
		ALLEGRO_BITMAP* enemy_bitmap;
		ALLEGRO_TIMER *timer;
		int start_time = 0;
		int speed = 2;

		Enemy();
		void move();
};

#endif
