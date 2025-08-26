#pragma once

#include "EntityComponentSystem.h"
#include <SDL.h>
#include "TextureManager.h"
#include "Vector2D.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	Vector2D position;

	TileComponent() = default;

	TileComponent(int sourceX, int sourceY, int xPosition, int yPosition, const char* path, int tileSize, int tileScale) {
		texture = TextureManager::LoadTexture(path);

		position.x = xPosition;
		position.y = yPosition;


		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
		sourceRect.w = sourceRect.h = tileSize;

		destinationRect.x = xPosition;
		destinationRect.y = yPosition;
		destinationRect.w = destinationRect.h = tileSize * tileScale;
	}
	void Draw() override {
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}

	void Update() override {
		destinationRect.x = position.x - Game::camera.x;
		destinationRect.y = position.y - Game::camera.y;
	}

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
};

