#pragma once
#include <string>
#include <SDL.h>	
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "Game.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

	TransformComponent* transform;

	ColliderComponent(std::string tag) {
		this->tag = tag;
	}

	ColliderComponent(std::string tag, int xPosition, int yPosition, int size) {
		this->tag = tag;

		collider.x = xPosition;
		collider.y = yPosition;

		collider.h = collider.w = size;
	}


	void Init() override {
		if (!entity->HasComponent<TransformComponent>()) {
			entity->AddComponent<TransformComponent>();
		}
		transform = &entity->GetComponent<TransformComponent>();

		collider.h = transform->height;
		collider.w = transform->width;

		texture = TextureManager::LoadTexture("resources/tiles/CollisionTexture.png");
		sourceRect = { 0,0,64,64 };
		destinationRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void Update() override {

		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			collider.w = static_cast<int>(transform->width * transform->scale);
			collider.h = static_cast<int>(transform->height * transform->scale);
		}
		destinationRect.x = collider.x - Game::camera.x;
		destinationRect.y = collider.y - Game::camera.y;
	}

	void Draw() override {
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}
};

