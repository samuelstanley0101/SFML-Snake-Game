#include <SFML/Graphics.hpp>
#include "Coords.hpp"
#include "Tiles.hpp"
using namespace sf;

Apple::Apple(int x, int y, const int& tilesize)
	: Tile(x, y, tilesize), circle(tilesize / 2)
{
	circle.setPosition(coords.x * tilesize, coords.y * tilesize);
	circle.setFillColor(Color::Red);
}

Apple::Apple(Coords coords, const int& tilesize)
	: Tile(coords, tilesize), circle(tilesize / 2)
{
	circle.setPosition(coords.x * tilesize, coords.y * tilesize);
	circle.setFillColor(Color::Red);
}

void Apple::draw(RenderWindow& window)
{
	circle.setPosition(coords.x * tilesize, coords.y * tilesize);
	window.draw(circle);
}

SnakeTile::SnakeTile(int x, int y, const int& tilesize, Color color = Color::Green)
	: Tile(x, y, tilesize)
{
	square = RectangleShape(Vector2f(tilesize, tilesize));
	square.setPosition(coords.x * tilesize, coords.y * tilesize);
	square.setFillColor(color);
}

SnakeTile::SnakeTile(Coords coords, const int& tilesize, Color color = Color::Green)
	: Tile(coords, tilesize)
{
	square = RectangleShape(Vector2f(tilesize, tilesize));
	square.setPosition(coords.x * tilesize, coords.y * tilesize);
	square.setFillColor(color);
}

void SnakeTile::draw(RenderWindow& window)
{
	square.setPosition(coords.x * tilesize, coords.y * tilesize);
	window.draw(square);
}