#include "Map.h"
#include "Game.h"
#include <fstream>
#include <sstream>
#include "EntityComponentSystem.h"
#include "TileComponent.h"
#include "ColliderComponent.h"

extern Manager manager;

Map::Map(const char* mapFilePath, int mapScale, int tileSize): mapFilePath(mapFilePath), mapScale(mapScale) {
	this->tileSize = tileSize;
	scaledSize = mapScale * tileSize;
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
			int sourceX = (tileId % 10) * tileSize;
			int sourceY = (tileId / 10) * tileSize;
			AddTile(sourceX, sourceY, x * scaledSize, y * scaledSize);
		}
	}
	// Consume possible blank separator lines between layers
	while (std::getline(mapFile, line)) {
		if (!line.empty()) {
			break;
		}
	}

	// Read collision layer: add colliders for cells with value '1'
	for (int y = 0; y < sizeY; y++) {
		if (y > 0) {
			if (!std::getline(mapFile, line)) {
				break;
			}
		}
		std::stringstream collisionLine(line);
		std::string collisionCell;
		for (int x = 0; x < sizeX; x++) {
			if (!std::getline(collisionLine, collisionCell, ',')) {
				break;
			}
			if (collisionCell == "1") {
				auto& colliderEntity(manager.AddEntity());
				colliderEntity.AddComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				auto& cc = colliderEntity.GetComponent<ColliderComponent>();
				cc.collider.x = x * scaledSize;
				cc.collider.y = y * scaledSize;
				cc.collider.w = scaledSize;
				cc.collider.h = scaledSize ;
				colliderEntity.AddGroup(Game::groupColliders);
			}
		}
	}

}

void Map::AddTile(int sourceX, int sourceY, int xPosition, int yPosition) {
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(sourceX, sourceY, xPosition, yPosition, mapFilePath, tileSize, mapScale);
	tile.AddGroup(Game::groupMap);
}

