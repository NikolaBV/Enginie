#pragma once
#include <string>
#include "EntityComponentSystem.h"
#include "AssetManager.h"

class Map
{
private:

public:
	Map(std::string textureId, int mapScale, int tileSize);
	~Map();

	void LoadMap(AssetManager& assetManager, Manager& manager, std::string path, int sizeX, int sizeY);
	void AddTile(AssetManager& assetManager, Manager& manager, int sourceX, int sourceY, int xPosition, int yPosition);

private:
	std::string textureId;
	int mapScale;
	int tileSize;
	int scaledSize;

};

