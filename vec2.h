#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

using namespace std;

class vec2
{
	public:
		int x;
		int y;

		vec2();
		vec2(int x, int y);
		static vec2 find_direction(vec2 from, vec2 to);
		static int distance(vec2 from, vec2 to);
		vec2 operator+(const vec2& v2);
		vec2 operator-(const vec2& v2);
		vec2 operator/(const int& d);
		friend bool operator==(const vec2 &v1, const vec2 &v2);
		friend ostream& operator<<(ostream& stream, const vec2& v);
};

#endif
