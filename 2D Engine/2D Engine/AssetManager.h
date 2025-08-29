#pragma once

#include <map>
#include <string>
#include "EntityComponentSystem.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();

	//gameObjects
	void CreateProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string textureId);

	//texture managmenent
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//Fonts
	void AddFont(std::string fontId, std::string path, int fontSize);
	TTF_Font* GetFont(std::string fontId);
	
private:	
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};

