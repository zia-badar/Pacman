#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <allegro5/allegro.h>
#include <cstdlib>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Waypoint.h"
#include "Pacman.h"
#include "Enemy.h"

using namespace std;

class Game
{
	public:
		int width;
		int height;
		vector<Waypoint> all_waypoints;
		Pacman pacman;
		vector<Enemy> all_enemies;
//		Enemy enemy;
		char** map;
		vector<vec2> all_points;
		int score = 0;
		int win_or_lose = 0;	//0: ingame, 1: win, 2: lose
		int game_state = 0;		// 0: start_screen, 1: paused

		int scale_size = 20;
		ALLEGRO_BITMAP* wall_bitmap;
		ALLEGRO_BITMAP* point_bitmap;
		ALLEGRO_TIMER* timer;
		ALLEGRO_FONT* font;
		ALLEGRO_FONT* font_small;

		Game();
		void update(ALLEGRO_EVENT* ev);
		void create_map_from_waypoints();
		void find_shortest_paths_to_pacman();
		void load_map_from_file();
		void set_timer(ALLEGRO_TIMER* timer);
};

#endif
