#include "Enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy()
{
//	enemy_bitmap = al_create_bitmap(scale_size, scale_size);
//	al_set_target_bitmap(enemy_bitmap);
//	al_clear_to_color(al_map_rgb(255, 0, 0));
	enemy_bitmap = al_load_bitmap("enemy.png");
}

void Enemy::move()
{
	if(!closest_waypoint_to_pacman)
	{
		al_draw_bitmap(enemy_bitmap, position.x*scale_size, position.y*scale_size, 0);
		return;
	}

	vec2 dir = vec2::find_direction(position, closest_waypoint_to_pacman->position);
	int time_past = al_get_timer_count(timer) - start_time;
	float speed_count = 60.0/speed;
	if(time_past > speed_count)
	{
		position = position + dir;
		start_time = al_get_timer_count(timer);
	}
	else
		al_draw_bitmap(enemy_bitmap, (position.x + dir.x*(time_past/speed_count))*scale_size
									, (position.y + dir.y*(time_past/speed_count))*scale_size, 0);


	if(position == closest_waypoint_to_pacman->position)
	{
		if(closest_waypoint_to_pacman->closest_waypoint_to_source->distance_to != 0)
			closest_waypoint_to_pacman = closest_waypoint_to_pacman->closest_waypoint_to_source;
		else
		{
			Waypoint* next_closest = closest_waypoint_to_pacman->closest_waypoint_to_source;
			vector<Waypoint*> adj_list = next_closest->adjacent_waypoints;
			bool check = false;
			for(int i=0; i<adj_list.size() && !check; i++)
				if(adj_list[i]->distance_to == 0)
					check = true;
			if(check)
					closest_waypoint_to_pacman = closest_waypoint_to_pacman->closest_waypoint_to_source;
			else
			{
				vec2 dir = vec2::find_direction(position, next_closest->position);
				closest_waypoint_to_pacman = next_closest->find_adjacent_in_direction(dir);
			}
		}
	}
}
