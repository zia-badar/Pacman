#include "Waypoint.h"

Waypoint::Waypoint()
{
	position.x = -1; position.y = -1;
	reset();
}

void Waypoint::reset()
{
	closest_waypoint_to_source = 0;
	distance_to = 1000;
	is_explored = false;
}

void Waypoint::remove_adjacent(Waypoint* adjacent)
{
	for(int i=0; i<adjacent_waypoints.size(); i++)
		if(adjacent_waypoints[i] == adjacent)
			adjacent_waypoints.erase(adjacent_waypoints.begin() + i);
}

void Waypoint::add_adjacent(Waypoint* adjacent)
{
	remove_adjacent(adjacent);
	adjacent_waypoints.push_back(adjacent);
}

Waypoint* Waypoint::find_adjacent_in_direction(vec2 direction)
{
	for(int i=0; i<adjacent_waypoints.size(); i++)
	{
		vec2 d = vec2::find_direction(position, adjacent_waypoints[i]->position);
		if(d == direction) return adjacent_waypoints[i];
	}
	return NULL;
}
