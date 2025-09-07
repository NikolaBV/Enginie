#pragma once
#include "SDL.h"
#include "EntityComponentSystem.h"
#include "AssetManager.h"
#include "EventBus.h"

class Game;

struct SceneContext {
	Game& game;
	EventBus& eventBus;
};

class Scene
{
public:
	virtual ~Scene() = default;
	virtual void OnEnter(SceneContext& sceneContext) = 0;
	virtual void OnExit(SceneContext& sceneContext) = 0;
	virtual void HandleEvent(SceneContext& sceneContext, const SDL_Event& e) = 0;
	virtual void Update(SceneContext& sceneContext) = 0;
	virtual void Render(SceneContext& sceneContext) = 0;

protected:
	Manager manager;
	AssetManager assets{ &manager };
};

