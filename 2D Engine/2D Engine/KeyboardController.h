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

	void Init() override {
		transform = &entity->GetComponent<TransformComponent>();
		sprite = &entity->GetComponent<SpriteComponent>();
	}

	void Update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				sprite->SetTexture("resources/standard/walk.png");
				transform->velocity.y = -1;
				sprite->Play("walkUp");
				break;
			case SDLK_a:
				sprite->SetTexture("resources/standard/walk.png");
				transform->velocity.x = -1;
				sprite->Play("walkLeft");
				break;
			case SDLK_s:
				sprite->SetTexture("resources/standard/walk.png");
				transform->velocity.y = 1;
				sprite->Play("walkDown");
				break;
			case SDLK_d:
				sprite->SetTexture("resources/standard/walk.png");
				sprite->Play("walkRight");
				transform->velocity.x = 1;
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				sprite->SetTexture("resources/standard/idle.png");
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_a:
				sprite->SetTexture("resources/standard/idle.png");
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_s:
				sprite->SetTexture("resources/standard/idle.png");
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_d:
				sprite->SetTexture("resources/standard/idle.png");
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			}
		}
	}
};

