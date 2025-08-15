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
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void SetTexture(const char* texturePath) {
		texture = TextureManager::LoadTexture(texturePath);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = transform->width;
		sourceRect.h = transform->height;
	}

	void Update() override
	{
		destinationRect.x = static_cast<int>(transform->position.x);
		destinationRect.y = static_cast<int>(transform->position.y);

		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;

	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}
};

