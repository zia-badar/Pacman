#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <vector>

#include "vec2.h"

using namespace std;

class Waypoint
{
	public:
		vec2 position;
		vector<Waypoint*> adjacent_waypoints;
		Waypoint *closest_waypoint_to_source;
		int distance_to;
		bool is_explored;

		Waypoint();
		void reset();
		void remove_adjacent(Waypoint* adjacent);
		void add_adjacent(Waypoint* adjacent);
		Waypoint* find_adjacent_in_direction(vec2 direction);
};

#endif
