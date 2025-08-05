#pragma once
#include <SDL.h>
#include "iostream"
#include <string>
#include <SDL_image.h>

class TextureManager
{
private:
public:
	static SDL_Texture* LoadTexture(const char* pathToFile, SDL_Renderer* renderer);
};

