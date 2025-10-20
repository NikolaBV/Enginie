#pragma once

#include <map>
#include <string>
#include "EntityComponentSystem.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

class AssetManager
{
public:
	AssetManager(Manager* manager);
	~AssetManager();

	//gameObjects
	void CreateProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string textureId, int damage);

	//texture managmenent
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//Fonts
	void AddFont(std::string fontId, std::string path, int fontSize);
	TTF_Font* GetFont(std::string fontId);

	//Add volume, stereo channels ect as function arguments
	//TODO Think about making a Sound class to export this functionality to and store a Sound class in the value of the map instead of a string to the url
	
	//TODO finish all functions
	void AddSoundEffect(std::string tag, std::string url);
	void GetSoundEffect(std::string tag);
	void RemoveSoundEffect(std::string tag);
	void PlaySound(std::string tag);
	void StopSound(std::string tag);

private:	
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Chunk*> soundEffects;
};

