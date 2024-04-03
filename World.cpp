#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <iostream> //DEBUG
#include <algorithm>
#include "Coords.hpp"
#include "World.hpp"
#include "Tiles.hpp"
using namespace sf;
using std::vector;
using std::cout; //DEBUG
using std::endl; //DEBUG
using std::find;

World::World(int width, int height, const int& tilesize)
	: tilesize(tilesize), apples()
{
	for (int y = 0; y < height; y++)
	{
		world.push_back(vector<Tile*>());
		for (int x = 0; x < width; x++)
		{
			world[y].push_back(new Tile(x, y, tilesize));
		}
	}

}

Tile*& World::at(int x, int y)
{
	if (y < world.size() && y >= 0)
	{
		if (x < world[y].size() && x >= 0)
		{
			return world[y][x];
		}
		else
			throw std::out_of_range("Out of Range error: invalid x value for World::at");
	}
	else
		throw std::out_of_range("Out of Range error: invalid y value for World::at");
}

Tile*& World::at(Coords coords)
{
	if (coords.y < world.size() && coords.y >= 0)
	{
		if (coords.x < world[coords.y].size() && coords.x >= 0)
		{
			return world[coords.y][coords.x];
		}
		else
			throw std::out_of_range("Out of Range error: invalid x value for World::at");
	}
	else
		throw std::out_of_range("Out of Range error: invalid y value for World::at");
}

bool World::validCoords(Coords coords)
{
	if (coords.y < world.size() && coords.y >= 0 && coords.x < world[coords.y].size() && coords.x >= 0)
	{
		if (!dynamic_cast<SnakeTile*>(world[coords.y][coords.x]))
		{
			return true;
		}
	}
	return false;
}

bool World::validCoords(int x, int y)
{
	if (y < world.size() && y >= 0 && x < world[y].size() && x >= 0)
	{
		if (!dynamic_cast<SnakeTile*>(world[y][x]))
		{
			return true;
		}
	}
	return false;
}

Coords World::randomCoords()
{
	vector<Coords> coords;
	for (int y = 0; y < world.size(); y++)
	{
		for (int x = 0; x < world[y].size(); x++)
		{
			if (validCoords(x, y) && !dynamic_cast<Apple*>(world[y][x]))
			{
				coords.push_back(world[y][x]->coords);
			}
		}
	}
	return coords[rand() % coords.size()];
}

bool World::move(Coords source, Coords destination)
{
	if (validCoords(destination))
	{
		delete at(destination);
		at(destination) = at(source);
		at(destination)->coords = destination;
		at(source) = new Tile(source, tilesize);
		return true;
	}
	else
		return false;
}

bool World::swap(Coords source, Coords destination)
{
	if (validCoords(destination))
	{
		std::swap(at(destination), at(source));
		at(destination)->coords = destination;
		at(source)->coords = source;
		return true;
	}
	else
		return false;
}

bool World::place(int x, int y, Tile* tile)
{
	if (!dynamic_cast<SnakeTile*>(at(x, y)) && !dynamic_cast<Apple*>(at(x, y))) //if x, y is a Tile
	{
		delete world[y][x];
		world[y][x] = tile;
		return true;
	}
	return false;
}

bool World::place(Coords coords, Tile* tile)
{
	if (!dynamic_cast<SnakeTile*>(at(coords)) && !dynamic_cast<Apple*>(at(coords))) //if coords is a Tile
	{
		delete world[coords.y][coords.x];
		world[coords.y][coords.x] = tile;
		return true;
	}
	return false;
}

void World::balance_apples()
{
	static int countdown;
	
	if (apples.size() <= 0 || (countdown <= 0 && apples.size() <= 5))
	{	
		Coords random_coords = randomCoords();
		if (!place(random_coords, new Apple(random_coords, tilesize)))
		{
			cout << "Failed to place apple at " << random_coords << endl; //DEBUG
			exit(1);
		}
		apples.push_back(random_coords);
		countdown = 10 + (rand() % 10);
	}
	else if (countdown <= 0)
	{
		countdown = 20;
	}
	countdown--;
}

void World::eat_apple(Coords coords)
{
	auto match = find(apples.begin(), apples.end(), coords);
	if (match != apples.end())
	{
		delete at(*match);
		at(*match) = new Tile(*match, tilesize);
		apples.erase(match);
	}
	else
	{
		cout << "No match was found" << endl; //DEBUG
	}
}

World::~World()
{
	for (int y = 0; y < world.size(); y++)
	{
		for (int x = 0; x < world[y].size(); x++)
		{
			delete world[y][x];
		}
	}
}