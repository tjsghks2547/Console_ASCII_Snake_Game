#include "Vector2.h"

Vector2::Vector2()
{
}

Vector2::Vector2(int x, int y)
	:x(x)
	,y(y)
{
}


Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x+other.x, y+other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}



bool Vector2::operator==(const Vector2& other) const
{
	return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return (x != other.x || y != other.y);
}



Vector2::operator COORD() const
{
	COORD coord = {};
	coord.X = static_cast<short>(x);
	coord.Y = static_cast<short>(y);

	return coord;
}
