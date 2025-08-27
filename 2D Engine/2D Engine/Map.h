#pragma once
#include <string>
class Map
{
private:

public:
	Map(std::string textureId, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int sourceX, int sourceY, int xPosition, int yPosition);

private:
	std::string textureId;
	int mapScale;
	int tileSize;
	int scaledSize;

};

