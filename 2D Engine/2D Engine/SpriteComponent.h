#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "Animation.h"
#include "AssetManager.h"
#include "Game.h"

#include <map>

class AssetManager;

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;

	bool animated = false;
	int frames = 0;
	int speed = 100; //delay between frames in miliseconds
		
public:
	AssetManager localAssetManager = nullptr;
	int animationIndex = 2;

	std::map<const char*, Animation> animations;

	SpriteComponent();
	SpriteComponent(AssetManager& assetManager,std::string textureId):localAssetManager(assetManager) {
		SetTexture(assetManager,textureId);
	}

	SpriteComponent(AssetManager& assetManager, std::string textureId, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 2, 200);

		Animation walkUp = Animation(0, 9, 100);
		Animation walkLeft = Animation(1, 9, 100);
		Animation walkDown = Animation(2, 9, 100);
		Animation walkRight = Animation(3, 9, 100);

		animations.emplace("idle", idle);

		animations.emplace("walkUp", walkUp);
		animations.emplace("walkLeft", walkLeft);
		animations.emplace("walkDown", walkDown);
		animations.emplace("walkRight", walkRight);

		Play("idle");

		SetTexture(assetManager,textureId);
	}

	void SetTexture(AssetManager& assetManager,std::string textureId) {
		texture = assetManager.GetTexture(textureId);
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

		if (animated) {
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		sourceRect.y = (animated ? animationIndex : 0) * transform->height;

		destinationRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destinationRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect);
	}

	void Play(const char* animationName) {
		frames = animations[animationName].frames;
		animationIndex = animations[animationName].index;
		speed = animations[animationName].speed;
	}
};

