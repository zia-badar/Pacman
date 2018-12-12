#include "Game.h"

Game::Game()
{
	wall_bitmap = al_create_bitmap(scale_size, scale_size);
	al_set_target_bitmap(wall_bitmap);
	al_clear_to_color(al_map_rgb(0, 0, 255));
	point_bitmap = al_load_bitmap("point.png");
	font = al_load_ttf_font("OpenSans-Regular.ttf", 75,0 );
	font_small = al_load_ttf_font("OpenSans-Regular.ttf", 15,0 );
}

void Game::update(ALLEGRO_EVENT* ev)
{
	if(ev->type == ALLEGRO_EVENT_KEY_DOWN && win_or_lose == 0)
		switch(ev->keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
				pacman.move(vec2(0, -1));
			break;
			case ALLEGRO_KEY_DOWN:
				pacman.move(vec2(0, 1));
			break;
			case ALLEGRO_KEY_LEFT:
				pacman.move(vec2(-1, 0));
			break;
			case ALLEGRO_KEY_RIGHT:
				pacman.move(vec2(1, 0));
			break;
			case ALLEGRO_KEY_SPACE:
				game_state = 2;
			break;
			case ALLEGRO_KEY_P:
				game_state = 1;
			break;
			case ALLEGRO_KEY_R:
				game_state = 2;
			break;
		}

	if(game_state == 0)
	{
		al_draw_text(font, al_map_rgb(255, 0, 0), 570/2, 660/2, ALLEGRO_ALIGN_CENTRE, "Start Game");
		return;
	}
	else if(game_state == 1)
	{
		al_draw_text(font, al_map_rgb(255, 0, 0), 570/2, 660/2, ALLEGRO_ALIGN_CENTRE, "Paused");
		return;
	}

	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			if(map[i][j] == 'o')
				al_draw_bitmap(wall_bitmap, j*scale_size, i*scale_size, 0);

	for(int i=0; i<all_points.size(); i++)
	{
		al_draw_bitmap(point_bitmap, all_points[i].x*scale_size, all_points[i].y*scale_size, 0);
	}
	create_map_from_waypoints();
	find_shortest_paths_to_pacman();
	for(int i=0; i<all_enemies.size(); i++)
	{
		all_enemies[i].move();
		if(all_enemies[i].position == pacman.waypoint.position)
		{
			all_enemies[i].closest_waypoint_to_pacman = NULL;
			win_or_lose = 2;
		}
	}
	pacman.move(vec2(0, 0));

	bool check = false;
	for(int i=0; i<all_points.size(); i++)
		if(pacman.waypoint.position == all_points[i])
		{
			all_points.erase(all_points.begin() + i);
			--i;
			check = true;
		}
	if(check == true)
		score++;

	if(all_points.size() == 0)
		win_or_lose = 1;

	if(win_or_lose == 1)
		al_draw_text(font, al_map_rgb(0,0,255), 570/2, 660/2, ALLEGRO_ALIGN_CENTRE, "You Win!");
	else if(win_or_lose == 2)
		al_draw_text(font, al_map_rgb(255, 0, 0), 570/2, 660/2, ALLEGRO_ALIGN_CENTRE, "You Lose!");

	string score_text = "Score: " + to_string(score);
	al_draw_text(font_small, al_map_rgb(255, 255, 255), 0, 630, ALLEGRO_ALIGN_LEFT, score_text.c_str());
}

void Game::create_map_from_waypoints()
{
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			map[i][j] = 'o';

	for(int i=0; i<all_waypoints.size(); i++)
	{
		Waypoint *waypoint = &all_waypoints[i];
		map[waypoint->position.y][waypoint->position.x] = '-';
		for(int j=0; j<waypoint->adjacent_waypoints.size(); j++)
		{
			for(vec2 from(waypoint->position.x, waypoint->position.y),
					 to = waypoint->adjacent_waypoints[j]->position;
					 !(from == to);)
			{
				vec2 direction = vec2::find_direction(from, to);
				from = from + direction;
				map[from.y][from.x] = '-';
			}
		}
	}

	Waypoint *waypoint = &pacman.waypoint;
	map[waypoint->position.y][waypoint->position.x] = 'P';
	for(int j=0; j<waypoint->adjacent_waypoints.size(); j++)
		for(vec2 from(waypoint->position.x, waypoint->position.y),
				 to = waypoint->adjacent_waypoints[j]->position;
				 !(from == to);)
		{
			vec2 direction = vec2::find_direction(from, to);
			from = from + direction;
			map[from.y][from.x] = '*';
		}

	for(int i=0; i<all_enemies.size(); i++)
		map[all_enemies[i].position.y][all_enemies[i].position.x] = 'E';

	//cout << "\033[2J";
	//for(int i=0; i<height; i++)
	//{
	//	for(int j=0; j<width; j++)
	//		cout << map[i][j] << " ";
	//	cout << endl;
	//}
}

void Game::find_shortest_paths_to_pacman()	// dijkstra's algorithm
{
	for(int i=0; i<all_waypoints.size(); i++)
	{
		all_waypoints[i].distance_to = 10000000;
		all_waypoints[i].is_explored = false;
		all_waypoints[i].closest_waypoint_to_source = NULL;
	}

	vector<Waypoint*> queue;
	queue.push_back(&pacman.waypoint);
	pacman.waypoint.is_explored = true;
	pacman.waypoint.distance_to = 0;

	while(!queue.empty())
	{
		Waypoint* head = queue.front();
		queue.erase(queue.begin()+0);

		for(int i=0; i<head->adjacent_waypoints.size(); i++)
		{
			Waypoint* w = head->adjacent_waypoints[i];
			if(head->distance_to + vec2::distance(head->position, w->position) < w->distance_to)
			{
				w->distance_to = head->distance_to + vec2::distance(head->position, w->position);
				w->closest_waypoint_to_source = head;
			}

			if(!w->is_explored)
			{
				queue.push_back(w);
				w->is_explored = true;
			}
		}
	}
}

void Game::load_map_from_file()
{
	string filename = "level1.map";
	ifstream fin(filename);
	fin >> width; fin >> height;
	int n_waypoints;
	fin >> n_waypoints;
	for(int i=0; i<n_waypoints; i++)
	{
		Waypoint waypoint;
		fin >> waypoint.position.x; fin >> waypoint.position.y;
		all_waypoints.push_back(waypoint);
	}
	int n_connections;
	fin >> n_connections;
	for(int i=0; i<n_connections; i++)
	{
		int wp_ind1, wp_ind2;
		fin >> wp_ind1; fin >> wp_ind2;
		all_waypoints[wp_ind1-1].adjacent_waypoints.push_back(&all_waypoints[wp_ind2-1]);
		all_waypoints[wp_ind2-1].adjacent_waypoints.push_back(&all_waypoints[wp_ind1-1]);

		vec2 v1 = all_waypoints[wp_ind1-1].position, v2 = all_waypoints[wp_ind2-1].position;
		all_points.push_back(vec2(v1.x, v1.y));
		for( vec2 from(v1.x, v1.y), to(v2.x, v2.y);
			!(from == to);)
		{
			vec2 direction = vec2::find_direction(from, to);
			from = from + direction;
			all_points.push_back(vec2(from.x, from.y));
		}
	}

	fin.close();

	map = (char**) malloc(sizeof(char*)*height);
	for(int i=0; i<height; i++)
		map[i] = (char*)malloc(sizeof(char)*width);

	pacman.jump_to(&all_waypoints[66], &all_waypoints[67]);
	pacman.waypoint.position = vec2(13, 23);
	find_shortest_paths_to_pacman();

	Enemy e1;
	e1.position = vec2(all_waypoints[0].position.x, all_waypoints[0].position.y);
	e1.closest_waypoint_to_pacman = all_waypoints[0].closest_waypoint_to_source;

	Enemy e2;
	e2.position = vec2(all_waypoints[62].position.x, all_waypoints[62].position.y);
	e2.closest_waypoint_to_pacman = all_waypoints[62].closest_waypoint_to_source;

	Enemy e3;
	e3.position = vec2(all_waypoints[5].position.x, all_waypoints[5].position.y);
	e3.closest_waypoint_to_pacman = all_waypoints[5].closest_waypoint_to_source;

Enemy e4;
	e4.position = vec2(all_waypoints[6].position.x, all_waypoints[6].position.y);
	e4.closest_waypoint_to_pacman = all_waypoints[6].closest_waypoint_to_source;


	all_enemies.push_back(e1);
	all_enemies.push_back(e2);
	all_enemies.push_back(e3);
	all_enemies.push_back(e4);
}

void Game::set_timer(ALLEGRO_TIMER* timer)
{
	this->timer = timer;
	pacman.timer = timer;
	for(int i=0; i<all_enemies.size(); i++)
		all_enemies[i].timer = timer;
}

