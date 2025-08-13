#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
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
		transform = &entity->GetComponent<TransformComponent>();

		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = 64;
		sourceRect.h = 64;

		destinationRect.w = 64;
		destinationRect.h = 64;
	}

	void Update() override
	{
		destinationRect.x = (int)transform->position.x;
		destinationRect.y = (int)transform->position.y;

	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}
};

