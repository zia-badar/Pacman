#include "vec2.h"

vec2::vec2()
{

}

vec2::vec2(int x, int y)
{
	this->x = x;
	this->y = y;
}

vec2 vec2::find_direction(vec2 from, vec2 to)
{
	if(from == to) return vec2(0, 0);
	vec2 direction = to - from;
	int distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	return direction/distance;
}

int vec2::distance(vec2 from, vec2 to)
{
	vec2 distance = to - from;
	return sqrt(pow(distance.x, 2) + pow(distance.y, 2));
}

vec2 vec2::operator+(const vec2 &v)
{
	return vec2(this->x + v.x, this->y + v.y);
}

vec2 vec2::operator-(const vec2 &v)
{
	return vec2(this->x - v.x, this->y - v.y);
}

vec2 vec2::operator/(const int& d)
{
	vec2 result;
	result.x = this->x/d;
	result.y = this->y/d;
	return result;
}

bool operator==(const vec2 &v1, const vec2 &v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

ostream& operator<<(ostream &stream, const vec2 &v)
{
	return stream << "(" << v.x << ", " << v.y << ")";
}
