#ifndef COORDS_H
#define COORDS_H

#include <iostream>
using std::ostream;

class Coords
{
public:
	Coords(int x, int y) : x(x), y(y) {}
	Coords operator+(Coords add);
	Coords& operator+=(Coords add);
	Coords operator*(Coords mult);
	Coords operator*(int mult);
	Coords& operator*=(int mult);
	bool operator==(Coords right);
	bool operator!=(Coords right);
	friend ostream& operator<<(ostream& out, const Coords& coords);
	static const Coords UP;
	static const Coords RIGHT;
	static const Coords DOWN;
	static const Coords LEFT;
	static const Coords NONE;
	int x;
	int y;
};

#endif