#pragma once

#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileId;
	const char* path;

	TileComponent() = default;
	TileComponent(int x, int y, int width, int height, int tileId) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = width;
		tileRect.h = height;
		this->tileId = tileId;

		switch (tileId) {
		case 0:
			path = "resources/tiles/water.png";
			break;
		case 1:
			path = "resources/tiles/dirt.png";
			break;
		case 2:
			path = "resources/tiles/grass.png";
			break;
		default:
			break;
		}
	}

	void Init() override {
		entity->AddComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y,tileRect.w, tileRect.y, 1);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(path);
		sprite = &entity->GetComponent <SpriteComponent>();
	}

};

