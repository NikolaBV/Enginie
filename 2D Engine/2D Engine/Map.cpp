#include "Map.h"
#include "Game.h"
#include <fstream>
#include <sstream>

Map::Map() {

}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	std::ifstream mapFile(path);
	if (!mapFile.is_open()) {
		return;
	}

	std::string line;
	for (int y = 0; y < sizeY; y++) {
		if (!std::getline(mapFile, line)) {
			break;
		}
		std::stringstream lineStream(line);
		std::string cell;
		for (int x = 0; x < sizeX; x++) {
			if (!std::getline(lineStream, cell, ',')) {
				break;
			}
			if (cell.empty()) {
				continue;
			}
			int tileId = std::stoi(cell);
			Game::AddTile(tileId, x, y);
		}
	}
}

