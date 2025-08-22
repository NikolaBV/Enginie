#pragma once

#include "EntityComponentSystem.h"
#include <SDL.h>
#include "TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;


	TileComponent() = default;

	TileComponent(int sourceX, int sourceY, int xPosition, int yPosition, const char* path) {
		texture = TextureManager::LoadTexture(path);
		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
		sourceRect.w = sourceRect.h = 64;

		destinationRect.x = xPosition;
		destinationRect.y = yPosition;
		destinationRect.w = destinationRect.h = 128;
	}
	void Draw() override {
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}


};

