#include "Pacman.h"

Pacman::Pacman()
{
//	pacman_bitmap = al_create_bitmap(scale_size, scale_size);
//	al_set_target_bitmap(pacman_bitmap);
//	al_clear_to_color(al_map_rgb(0, 255, 0));
	pacman_bitmap = al_load_bitmap("pacman.png");
}

void Pacman::move(vec2 direction)
{
	if(!(direction == vec2(0, 0)))
	{
		if(source)
		{
			Waypoint* new_destination = waypoint.find_adjacent_in_direction(direction);
			Waypoint* new_source = waypoint.find_adjacent_in_direction(vec2(0, 0)-direction);
			if(new_destination != NULL && new_source != NULL)
			{
				destination = new_destination;
				source = new_source;
			}
		}
		else
		{
			Waypoint* new_destination = waypoint.adjacent_waypoints[0]->find_adjacent_in_direction(direction);
			if(new_destination != NULL)
			{
				destination = new_destination;
				source = waypoint.adjacent_waypoints[0];
				jump_to(source, destination);
			}
		}
	}

	if(source)
	{
		int time_past = al_get_timer_count(timer) - start_time;
		vec2 dir = vec2::find_direction(source->position, destination->position);
		if(time_past > (60/speed))
		{
			waypoint.position = waypoint.position + dir;
			if(waypoint.position == destination->position)
			{
				source->remove_adjacent(&waypoint);
				waypoint.remove_adjacent(source);
				source->add_adjacent(destination);
				destination->add_adjacent(source);
				source = NULL;
				destination = NULL;
			}
			start_time = al_get_timer_count(timer);
		}
		else
		{
			float speed_count = (60.0/speed);
			al_draw_bitmap(pacman_bitmap, (waypoint.position.x + dir.x*(time_past/speed_count))*scale_size
										, (waypoint.position.y + dir.y*(time_past/speed_count))*scale_size, 0);
		}
	}
	else
		al_draw_bitmap(pacman_bitmap, waypoint.position.x*scale_size, waypoint.position.y*scale_size, 0);


}

void Pacman::jump_to(Waypoint* s, Waypoint* d)
{
	source = s;
	destination = d;
	source->remove_adjacent(destination);
	destination->remove_adjacent(source);
	source->add_adjacent(&waypoint);
	waypoint.add_adjacent(source);
	destination->add_adjacent(&waypoint);
	waypoint.add_adjacent(destination);
}
