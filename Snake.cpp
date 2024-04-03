#include <SFML/Graphics.hpp>
#include <iostream> //DEBUG
#include <list>
#include <stdexcept>
#include "Snake.hpp"
#include "Coords.hpp"
#include "Tiles.hpp"
#include "World.hpp"
using namespace sf;
using std::list;
using std::cout;
using std::endl;
using std::swap;
using std::out_of_range;

Snake::Snake(int x, int y, Color color, World& world)
	: color(color), speed(1), sprinting(1), stamina(20), direction(Coords::NONE), world(world), alive(true), exhausted(false)
{
	world.at(x, y) = new SnakeTile(x, y, world.tilesize, color);
	body.push_front(Coords(x, y));
}

Snake::Snake(Coords coords, Color color, World& world)
	: color(color), speed(1), sprinting(1), stamina(20), direction(Coords::NONE), world(world), alive(true), exhausted(false)
{
	world.at(coords) = new SnakeTile(coords, world.tilesize, color);
	body.push_front(coords);
}

void Snake::temp_set_color(Color color)
{
	for (auto i = body.begin(); i != body.end(); i++)
	{
		static_cast<SnakeTile*>(world.at(*i))->set_color(color);
	}
}

bool Snake::inSnake(Coords coords)
{
	if (!world.validCoords(coords))
		return false;
	for (auto i = body.begin(); i != body.end(); i++)
	{
		if (*i == coords)
			return true;
	}
	return false;
}

Coords Snake::bodyAt(int index)
{
	int j = 0;
	for (auto i = body.begin(); i != body.end(); i++)
	{
		if (j == index)
			return *i;
		j++;
	}
}

bool Snake::move()
{
	//check if Snake is trying to move back in on itself
	if (body.size() > 1 && body.front() + direction == bodyAt(1))
	{
		direction *= -1; //reverse direction
	}

	Coords source = body.back();
	Coords destination = body.front() + direction;
	//check if direction is valid
	if (world.validCoords(destination) && direction != Coords::NONE && sprinting % 2 == 0)
	{
		//check if eating apple
		if (dynamic_cast<Apple*>(world.at(destination)))
		{
			world.eat_apple(destination);
			world.place(destination, new SnakeTile(destination, world.tilesize, dynamic_cast<SnakeTile*>(world.at(body.front()))->get_color()));
			body.push_front(destination);
		}
		else //normal move
		{
			world.move(source, destination);
			body.push_front(destination);
			body.pop_back();
		}
		sprinting = 1;
		return true;
	}
	else if (direction != Coords::NONE && sprinting % 2 == 0) //if coords are invalid and Snake is moving
	{
		return false;
	}
	if (sprinting == 1)
		sprinting--;
	return true;
}

void Snake::sprint()
{
	if (!exhausted)
	{
		sprinting = 2;
	}
}

void Snake::manage_stamina()
{
	if (sprinting == 2 && !exhausted)
	{
		stamina--;
	}
	if (stamina < 20 && sprinting != 2)
	{
		stamina++;
	}
	if (stamina == 0)
	{
		exhausted = true;
	}
	if (stamina == 20)
	{
		exhausted = false;
	}

	if (stamina < 5)
	{
		Color temp_color = color;
		temp_color.r += 80;
		temp_color.g += 80;
		temp_color.b += 80;
		temp_set_color(temp_color);
	}
	else if (stamina < 10)
	{
		Color temp_color = color;
		temp_color.r += 60;
		temp_color.g += 60;
		temp_color.b += 60;
		temp_set_color(temp_color);
	}
	else if (stamina < 15)
	{
		Color temp_color = color;
		temp_color.r += 40;
		temp_color.g += 40;
		temp_color.b += 40;
		temp_set_color(temp_color);
	}
	else if (stamina < 20)
	{
		Color temp_color = color;
		temp_color.r += 20;
		temp_color.g += 20;
		temp_color.b += 20;
		temp_set_color(temp_color);
	}
	else if (stamina == 20)
	{
		temp_set_color(color);
	}

	
}