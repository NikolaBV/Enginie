#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	AssetManager localAssetManager = nullptr;

	KeyboardController(AssetManager& assetManager):localAssetManager(assetManager) {}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				sprite->SetTexture(localAssetManager, "playerWalk");
				transform->velocity.y = -1;
				sprite->Play("walkUp");
				break;
			case SDLK_a:
				sprite->SetTexture(localAssetManager,"playerWalk");
				transform->velocity.x = -1;
				sprite->Play("walkLeft");
				break;
			case SDLK_s:
				sprite->SetTexture(localAssetManager,"playerWalk");
				transform->velocity.y = 1;
				sprite->Play("walkDown");
				break;
			case SDLK_d:
				sprite->SetTexture(localAssetManager,"playerWalk");
				sprite->Play("walkRight");
				transform->velocity.x = 1;
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				sprite->SetTexture(localAssetManager, "playerIdle");
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_a:
				sprite->SetTexture(localAssetManager, "playerIdle");
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_s:
				sprite->SetTexture(localAssetManager, "playerIdle");
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_d:
				sprite->SetTexture(localAssetManager, "playerIdle");
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			}
		}
	}


	KeyboardController() = default;
};

