#pragma once
#include "Scene.h"
#include "Map.h"
#include "Components.h"
#include "TransformComponent.h"
#include "Collision.h"
#include "UILabelComponent.h"
#include "ColliderComponent.h"

#include <sstream>
#include <vector>

class Map;

class SandboxScene :public Scene
{
public:
	void OnEnter(SceneContext& sceneContext) override;
	void OnExit(SceneContext& sceneContext) override;
	void HandleEvent(SceneContext& sceneContext, const SDL_Event& e) override;
	void Update(SceneContext& sceneContext) override;
	void Render(SceneContext& sceneContext) override;
private:
	std::unique_ptr<Map> map;
	Entity* playerEntity = nullptr;
	Entity* labelEntity = nullptr;
};

