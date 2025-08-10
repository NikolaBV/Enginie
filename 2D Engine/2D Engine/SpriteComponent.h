#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "EntityComponentSystem.h"
#include "PositionComponent.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* texturePath) {
		SetTexture(texturePath);
	}

	void SetTexture(const char* texturePath) {
		texture = TextureManager::LoadTexture(texturePath);
	}

	void Init() override
	{
		position = &entity->GetComponent<PositionComponent>();

		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = 64;
		sourceRect.h = 64;

		destinationRect.w = 64;
		destinationRect.h = 64;
	}

	void Update() override
	{
		destinationRect.x = position->getX();
		destinationRect.y = position->getY();

	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}
};

