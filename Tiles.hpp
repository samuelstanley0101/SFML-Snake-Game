#ifndef TILES_H
#define TILES_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Coords.hpp"
#include "Forward_Declarations.hpp"
using namespace sf;
using std::string;

class Tile
{
public:
	Tile(int x, int y, const int& tilesize) : coords(x, y), tilesize(tilesize) {}
	Tile(Coords coords, const int& tilesize) : coords(coords), tilesize(tilesize) {}
	inline Coords getCoords() const { return coords; }
	inline virtual void draw(RenderWindow& window) {};
	friend class World;
	const int& tilesize;
protected:
	Coords coords;
};

class Apple : public Tile
{
public:
	Apple(int x, int y, const int& tilesize);
	Apple(Coords coords, const int& tilesize);
	void draw(RenderWindow& window);
protected:
	CircleShape circle;
};

class SnakeTile : public Tile
{
public:
	SnakeTile(int x, int y, const int& tilesize, Color color);
	SnakeTile(Coords coords, const int& tilesize, Color color);
	void draw(RenderWindow& window);
	inline Color get_color() { return square.getFillColor(); }
	inline void set_color(Color color) { square.setFillColor(color); }
private:
	RectangleShape square;
};

#endif