#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* pathToFile, SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(pathToFile);
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}