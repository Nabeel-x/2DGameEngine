#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map() {}
Map::~Map() {}

void Map::LoadMap(std::string path, int sizex, int sizey) {
	char tile;
	std::fstream mapfile;
	mapfile.open(path);
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			mapfile.get(tile);
			Game::addTile(atoi(&tile),x*32,y*32);
			mapfile.ignore();
		}
	}
	mapfile.close();
}