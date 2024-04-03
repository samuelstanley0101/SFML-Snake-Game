#include "Coords.hpp"
#include <iostream>
using std::ostream;

Coords Coords::operator+(Coords add)
{
	return Coords(x + add.x, y + add.y);
}

Coords& Coords::operator+=(Coords add) {
	x += add.x;
	y += add.y;
	return *this;
}

Coords Coords::operator*(Coords mult)
{
	return Coords(x * mult.x, y * mult.y);
}

Coords Coords::operator*(int mult)
{
	return Coords(x * mult, y * mult);
}

Coords& Coords::operator*=(int mult)
{
	x *= mult;
	y *= mult;
	return *this;
}

bool Coords::operator==(Coords right)
{
	if (x == right.x && y == right.y)
		return true;
	else
		return false;
}

bool Coords::operator!=(Coords right)
{
	if (x != right.x || y != right.y)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const Coords& coords)
{
	return out << "(" << coords.x << ", " << coords.y << ")";
}

const Coords Coords::UP(0, -1);
const Coords Coords::RIGHT(1, 0);
const Coords Coords::DOWN(0, 1);
const Coords Coords::LEFT(-1, 0);
const Coords Coords::NONE(0, 0);