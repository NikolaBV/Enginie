#pragma once
#include <string>
class Map
{
private:

public:
	Map(const char* mapFilePath, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int sourceX, int sourceY, int xPosition, int yPosition);

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;

};

