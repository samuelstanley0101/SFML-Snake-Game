#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "Coords.hpp"
#include "Forward_Declarations.hpp"
#include "Tiles.hpp"
using namespace sf;
using std::list;

class Snake
{
public:
	Snake(int x, int y, Color color, World& world);
	Snake(Coords coords, Color color, World& world);
	void temp_set_color(Color color);
	//Precondition: None.
	//Postcondition: If the tile at coords is part of Snake, true has been returned, otherwise false
	//has been returned.
	bool inSnake(Coords coords);
	Coords bodyAt(int index);
	inline int size() { return body.size(); }
	//Precondition: None.
	//Postcondition: If Snake can move according to its direction and speed, it will move and true will
	//be returned (if direction would go back on itself, Snake just moves opposite of direction). If
	//Snake cannot move according to its direction and speed. false will be returned.
	bool move();
	void sprint();
	void manage_stamina();
	Coords direction;
	bool alive;
private:
	Color color;
	list<Coords> body;
	int speed;
	int sprinting;
	int stamina;
	World& world;
	bool exhausted;
};

#endif