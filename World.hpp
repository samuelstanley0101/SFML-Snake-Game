#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Coords.hpp"
#include "Forward_Declarations.hpp"
#include "Snake.hpp"
using std::vector;

class World
{
public:
	World(int width, int height, const int& tilesize);
	Tile*& at(int x, int y);
	Tile*& at(Coords coords);
	bool validCoords(Coords coords);
	bool validCoords(int x, int y);
	Coords randomCoords();
	//Precondition: source is a valid tile location.
	//Postcondition: If destination is a valid set of coordinates, the tile at source has been moved to
	//destination, replacing whatever was there before, a new Tile has been placed at source, and true has
	//been returned. If destination is not valid, false has been returned.
	bool move(Coords source, Coords destination);
	//Precondition: source is a valid tile location.
	//Postcondition: If destination is a valid set of coordinates, the tiles at source and destination have been
	//swapped and true has been returned. If destination is not valid, false has been returned.
	bool swap(Coords source, Coords destination);
	bool place(int x, int y, Tile* tile);
	bool place(Coords coords, Tile* tile);
	//Precondition: None.
	//Postcondition: An apple has been placed every 10 - 20 turns until there are 6 apples on the board. If there
	//are no apples on the board, one will be placed immediately.
	void balance_apples();
	//Preconditon: A snake, in this turn, is about to eat the apple at coords.
	//Postcondition: The apple at coords has been removed from apples and has been deleted and replaced with a Tile.
	void eat_apple(Coords coords);
	~World();
	const int& tilesize;
private:
	vector<vector<Tile*>> world;
	vector<Coords> apples;
};

#endif