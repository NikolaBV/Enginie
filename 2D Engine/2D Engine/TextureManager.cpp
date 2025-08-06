#include "TextureManager.h"

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourcePosition, SDL_Rect destinationPosition)
{
	SDL_RenderCopy(Game::renderer, texture, &sourcePosition, &destinationPosition);
}

SDL_Texture* TextureManager::LoadTexture(const char* pathToFile) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(pathToFile);
	if (surface == NULL) {
		std::cout << "Error loading texture: " << pathToFile << " - " << IMG_GetError() << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		if (texture == NULL) {
			std::cout << "Error creating texture from surface: " << pathToFile << " - " << SDL_GetError() << std::endl;
		}
	}

	SDL_FreeSurface(surface);

	return texture;
}