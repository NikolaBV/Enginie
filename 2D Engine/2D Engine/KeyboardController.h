#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <map>
#include "InputScheme.h"

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

	InputScheme inputScheme = InputScheme::Both;
	const char* defaultWalkTextureId = "playerWalk";
	const char* defaultIdleTextureId = "playerIdle";

	void SetInputScheme(InputScheme scheme) { inputScheme = scheme; }


	KeyboardController();

	KeyboardController(AssetManager& assetManager, const Uint8* keyState, std::map<SDL_Scancode, const char*> textureKeyboardControlMap, bool horizontalMovement, bool verticalMovement)
		:localAssetManager(assetManager), localKeyState(keyState), textureKeyboardControlMap(textureKeyboardControlMap), horizontalMovement(horizontalMovement), verticalMovement(verticalMovement) {
	}

	KeyboardController(AssetManager& assetManager, const Uint8* keyState, std::map<SDL_Scancode, const char*> textureKeyboardControlMap, bool horizontalMovement, bool verticalMovement, InputScheme scheme)
		:localAssetManager(assetManager), localKeyState(keyState), textureKeyboardControlMap(textureKeyboardControlMap), horizontalMovement(horizontalMovement), verticalMovement(verticalMovement), inputScheme(scheme) {
	}

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override {
		const bool wasdUp = localKeyState[SDL_SCANCODE_W];
		const bool wasdDown = localKeyState[SDL_SCANCODE_S];
		const bool wasdLeft = localKeyState[SDL_SCANCODE_A];
		const bool wasdRight = localKeyState[SDL_SCANCODE_D];

		const bool arrowsUp = localKeyState[SDL_SCANCODE_UP];
		const bool arrowsDown = localKeyState[SDL_SCANCODE_DOWN];
		const bool arrowsLeft = localKeyState[SDL_SCANCODE_LEFT];
		const bool arrowsRight = localKeyState[SDL_SCANCODE_RIGHT];

		auto isSchemeEnabled = [this](InputScheme required) {
			return inputScheme == required || inputScheme == InputScheme::Both;
		};

		bool upPressed = (isSchemeEnabled(InputScheme::WASD) && wasdUp) || (isSchemeEnabled(InputScheme::Arrows) && arrowsUp);
		bool downPressed = (isSchemeEnabled(InputScheme::WASD) && wasdDown) || (isSchemeEnabled(InputScheme::Arrows) && arrowsDown);
		bool leftPressed = (isSchemeEnabled(InputScheme::WASD) && wasdLeft) || (isSchemeEnabled(InputScheme::Arrows) && arrowsLeft);
		bool rightPressed = (isSchemeEnabled(InputScheme::WASD) && wasdRight) || (isSchemeEnabled(InputScheme::Arrows) && arrowsRight);

		transform->velocity.x = 0;
		transform->velocity.y = 0;

		if (verticalMovement) {
			if (upPressed && !downPressed) {
				transform->velocity.y = -1;
			}
			else if (downPressed && !upPressed) {
				transform->velocity.y = 1;
			}
		}

		if (horizontalMovement) {
			if (rightPressed && !leftPressed) {
				transform->velocity.x = 1;
			}
			else if (leftPressed && !rightPressed) {
				transform->velocity.x = -1;
			}
		}

		if ((transform->velocity.x != 0) && (transform->velocity.y != 0)) {
			transform->speed = 2;
		}
		else if ((transform->velocity.x != 0) || (transform->velocity.y != 0)) {
			transform->speed = 3;
		} else {
			transform->speed = 0;
		}

		auto setTextureFor = [this](SDL_Scancode primary, SDL_Scancode fallback) {
			auto itPrimary = textureKeyboardControlMap.find(primary);
			if (itPrimary != textureKeyboardControlMap.end()) {
				sprite->SetTexture(localAssetManager, itPrimary->second);
				return;
			}
			auto itFallback = textureKeyboardControlMap.find(fallback);
			if (itFallback != textureKeyboardControlMap.end()) {
				sprite->SetTexture(localAssetManager, itFallback->second);
				return;
			}
			sprite->SetTexture(localAssetManager, defaultWalkTextureId);
		};

		if (transform->velocity.y == -1) {
			// Up
			if (isSchemeEnabled(InputScheme::WASD) && wasdUp) setTextureFor(SDL_SCANCODE_W, SDL_SCANCODE_UP);
			else if (isSchemeEnabled(InputScheme::Arrows) && arrowsUp) setTextureFor(SDL_SCANCODE_UP, SDL_SCANCODE_W);
			sprite->Play("walkUp");
		}
		else if (transform->velocity.y == 1) {
			// Down
			if (isSchemeEnabled(InputScheme::WASD) && wasdDown) setTextureFor(SDL_SCANCODE_S, SDL_SCANCODE_DOWN);
			else if (isSchemeEnabled(InputScheme::Arrows) && arrowsDown) setTextureFor(SDL_SCANCODE_DOWN, SDL_SCANCODE_S);
			sprite->Play("walkDown");
		}
		else if (transform->velocity.x == 1) {
			// Right
			if (isSchemeEnabled(InputScheme::WASD) && wasdRight) setTextureFor(SDL_SCANCODE_D, SDL_SCANCODE_RIGHT);
			else if (isSchemeEnabled(InputScheme::Arrows) && arrowsRight) setTextureFor(SDL_SCANCODE_RIGHT, SDL_SCANCODE_D);
			sprite->Play("walkRight");
		}
		else if (transform->velocity.x == -1) {
			// Left
			if (isSchemeEnabled(InputScheme::WASD) && wasdLeft) setTextureFor(SDL_SCANCODE_A, SDL_SCANCODE_LEFT);
			else if (isSchemeEnabled(InputScheme::Arrows) && arrowsLeft) setTextureFor(SDL_SCANCODE_LEFT, SDL_SCANCODE_A);
			sprite->Play("walkLeft");
		}
		else {
			sprite->Play("idle");
		}
	}
};

