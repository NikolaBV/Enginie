#pragma once
#include <SDL.h>
#include "iostream"
#include <string>
#include <SDL_image.h>
#include "Game.h"

class TextureManager
{
private:
public:
	static void Draw(SDL_Texture* texture, SDL_Rect sourcePosition, SDL_Rect destinationPosition);
	static SDL_Texture* LoadTexture(const char* pathToFile);
};

