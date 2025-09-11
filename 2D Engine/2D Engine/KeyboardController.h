#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <map>

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	AssetManager localAssetManager = nullptr;
	const Uint8* localKeyState;
	std::map< SDL_Scancode, const char*> textureKeyboardControlMap;
	bool verticalMovement;
	bool horizontalMovement;


	KeyboardController();

	KeyboardController(AssetManager& assetManager, const Uint8* keyState, std::map<SDL_Scancode, const char*> textureKeyboardControlMap, bool horizontalMovement, bool verticalMovement)
		:localAssetManager(assetManager), localKeyState(keyState), textureKeyboardControlMap(textureKeyboardControlMap), horizontalMovement(horizontalMovement), verticalMovement(verticalMovement) {
	}

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
			transform->speed = 2;
		}
		else {
			transform->speed = 3;
		}

		//TODO Fix hardcoded texture ids (right now this component is ONLY meant to work with these playerWalk ect texture ids, make this generic and pass necessery texture ids in 
		// conditionally (for example, if the entity is allowed horizontal and vertical position changes or only one of the 2)

		if (verticalMovement && horizontalMovement) {
			if (localKeyState[SDL_SCANCODE_W]) {
				sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_W]);
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
		else if (verticalMovement && !horizontalMovement) {
			if (localKeyState[SDL_SCANCODE_W]) {
				sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_W]);
				transform->velocity.y = -1;
				sprite->Play("walkUp");
			}
			else if (localKeyState[SDL_SCANCODE_S]) {
				sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_S]);
				transform->velocity.y = 1;
				sprite->Play("walkDown");
			}
			if (localKeyState[SDL_SCANCODE_UP]) {
				sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_W]);
				transform->velocity.y = -1;
				sprite->Play("walkUp");
			}
			else if (localKeyState[SDL_SCANCODE_DOWN]) {
				sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_S]);
				transform->velocity.y = 1;
				sprite->Play("walkDown");
			}

			if (Game::event.type == SDL_KEYUP) {
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:
					sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_W]);
					transform->velocity.y = 0;
					sprite->Play("idle");
					break;
				case SDLK_s:
					sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_S]);
					transform->velocity.y = 0;
					sprite->Play("idle");
					break;
				case SDLK_UP:
					sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_W]);
					transform->velocity.y = 0;
					sprite->Play("idle");
					break;
				case SDLK_DOWN:
					sprite->SetTexture(localAssetManager, textureKeyboardControlMap[SDL_SCANCODE_S]);
					transform->velocity.y = 0;
					sprite->Play("idle");
					break;
				}

			}
		}


	}
};

