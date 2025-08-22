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
			// Cells encode source coordinates as two digits: XY -> (sourceX=X, sourceY=Y)
			if (cell.length() < 2) {
				continue;
			}
			int tileId = std::stoi(cell);
			int sourceX = (tileId % 10) * 64;
			int sourceY = (tileId / 10) * 64;
			Game::AddTile(sourceX, sourceY, x * 128, y * 128);
		}
	}
}

