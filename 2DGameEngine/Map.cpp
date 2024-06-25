#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map() {}
Map::~Map() {}

void Map::LoadMap(std::string path, int sizex, int sizey) {
	char c;
	std::fstream mapfile;
	int srcX, srcY;
	mapfile.open(path);
	for (int y = 0; y < sizey; y++) {
		for (int x = 0; x < sizex; x++) {
			mapfile.get(c);
			srcY = atoi(&c) * 32;
			mapfile.get(c);
			srcX = atoi(&c) * 32;
			Game::addTile(srcX,srcY, x * 64, y * 64);
			mapfile.ignore();
		}
	}
	mapfile.close();
}