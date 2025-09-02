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
	const Uint8* localKeyState;

	KeyboardController();

	KeyboardController(AssetManager& assetManager, const Uint8* keyState) :localAssetManager(assetManager), localKeyState(keyState) {}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override {
		//TODO This seems like it might be a problem in the future, its a quick fix, not very much tested, thing of something better
		
		//std::cout << "W:" << (int)localKeyState[SDL_SCANCODE_W]
		//	<< " A:" << (int)localKeyState[SDL_SCANCODE_A]
		//	<< " S:" << (int)localKeyState[SDL_SCANCODE_S]
		//	<< " D:" << (int)localKeyState[SDL_SCANCODE_D]
		//	<< std::endl;
		if (((int)localKeyState[SDL_SCANCODE_W] == 1 && (int)localKeyState[SDL_SCANCODE_D] == 1) ||
			((int)localKeyState[SDL_SCANCODE_W] == 1 && (int)localKeyState[SDL_SCANCODE_A] == 1) ||
			((int)localKeyState[SDL_SCANCODE_S] == 1 && (int)localKeyState[SDL_SCANCODE_D] == 1) ||
			((int)localKeyState[SDL_SCANCODE_S] == 1 && (int)localKeyState[SDL_SCANCODE_A] == 1)
			) {
			std::cout << "diagonal movement" << std::endl;
			transform->speed = 2;
		}
		else {
			transform->speed = 3;
		}

		if (localKeyState[SDL_SCANCODE_W]) {
			sprite->SetTexture(localAssetManager, "playerWalk");
			transform->velocity.y = -1;
			sprite->Play("walkUp");
		}
		else if (localKeyState[SDL_SCANCODE_S]) {
			sprite->SetTexture(localAssetManager, "playerWalk");
			transform->velocity.y = 1;
			sprite->Play("walkDown");
		}
		else if (localKeyState[SDL_SCANCODE_D]) {
			sprite->SetTexture(localAssetManager, "playerWalk");
			sprite->Play("walkRight");
			transform->velocity.x = 1;
		}
		else if (localKeyState[SDL_SCANCODE_A]) {
			sprite->SetTexture(localAssetManager, "playerWalk");
			transform->velocity.x = -1;
			sprite->Play("walkLeft");
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
};

